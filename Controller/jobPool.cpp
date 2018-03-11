//
// Created by Zippo Xie on 2/21/18.
//
#include "jobPool.h"

ostream &operator<<(ostream &output, const jobPool &A) {
    output << "***********jobPool Debug info***********\n";
    output << "Configs:\n";
    output << "Last_studied: " << ctime(&A.last_studied);
    output << "Last_new: " << A.last_new << endl;
    output << "last_review: " << A.last_review << endl;
    output << "Max_new: " << A.max_new << endl;
    output << "max_review: " << A.max_review << endl;
    output << "learning_steps: ";
    for(auto it = A.learning_steps.begin(); it != A.learning_steps.end(); ++it)
        output << *it << " ";
    output << "\n";
    output << "New cards:\n";
    for(auto it = A.new_card_list.begin(); it != A.new_card_list.end(); ++it)
        output << *it;
    output << "Listing new cards finished\n";

    output << "Old cards:\n";
    for(auto it = A.review_card_list.begin(); it != A.review_card_list.end(); ++it)
        output << *it;
    output << "Listing old cards finished\n";

    output << "Over\n\n";
    return output;
}

jobPool::jobPool(string username, string password) {
    id = username + password;
    update_card_list();
    update_config();
}
void jobPool::update_config() {
    learning_steps.clear();
    auto collection = db[id];
    bsoncxx::stdx::optional<bsoncxx::document::value> config =
      collection.find_one(document{} << "type" << "config" << finalize);
    if(!config) {
        // default configs
        time_t now = time(0);
        auto config = bsoncxx::builder::stream::document{} 
                << "type" << "config"
                << "last_studied@" << (long long int)(now) //////////////////
                << "last_new" << 0
                << "last_review" << 0
                << "max_new" << 20
                << "max_review" << 600
                << "learning_steps" << open_array
                    << 60 << 300 << 1800 << 43200 << close_array // 1mins, 5mins, 30mins, 12hrs
                << bsoncxx::builder::stream::finalize;
        collection.insert_one(config.view());
        learning_steps = {60, 300, 1800, 43200}; 
        max_new = 20;
        last_new = 0;
        max_review = 600;
        last_review = 0;
        last_studied = now;
    } else {
        time_t start_of_today, now;
        now = time(0);
        tm* tm = localtime(&now);
        tm->tm_hour = 24;
        tm->tm_min = 0;
        tm->tm_sec = 0;
        tm->tm_mday --;
        start_of_today = mktime(tm);

        auto config_view = config->view();
        bsoncxx::document::element last_studied_ele = config_view["last_studied@"];
        bsoncxx::document::element max_new_ele = config_view["max_new"];
        bsoncxx::document::element last_new_ele = config_view["last_new"];
        bsoncxx::document::element last_review_ele = config_view["last_review"];
        bsoncxx::document::element max_review_ele = config_view["max_review"];
        bsoncxx::document::element learning_steps_array_ele = config_view["learning_steps"];

        if(last_studied_ele && last_studied_ele.type() == type::k_int64) {
            if(last_studied_ele.get_int64().value < start_of_today) {
                last_new = 0;
                last_review = 0;
            } else {
                if(last_new_ele && last_new_ele.type() == type::k_int32) {
                    last_new = last_new_ele.get_int32().value;
                }
                if(last_review_ele && last_review_ele.type() == type::k_int32) {
                    last_review = last_review_ele.get_int32().value;
                }
            }
            last_studied = time(0);
        }

        if(max_new_ele && max_new_ele.type() == type::k_int32) {
            max_new = max_new_ele.get_int32().value;
        }
        if(max_review_ele && max_review_ele.type() == type::k_int32) {
            max_review = max_review_ele.get_int32().value;
        }
        if(learning_steps_array_ele && learning_steps_array_ele.type() == type::k_array) {
            for(const bsoncxx::array::element& one_int : learning_steps_array_ele.get_array().value) {
                if(one_int.type() == type::k_int32) {
                    learning_steps.push_back(one_int.get_int32().value);
                } else {cout << "Illegal config format!" << endl;}
            }
        }
    }
}


void jobPool::update_card_list() {
    time_t end_of_today, now;
    now = time(0);
    tm* tm = localtime(&now);
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    tm->tm_mday ++;
    end_of_today = mktime(tm);
    
    auto collection = db[id];

    bsoncxx::stdx::optional<bsoncxx::document::value> not_first_time =
      collection.find_one(document{} << "init" << "record" << finalize);
    if(!not_first_time) {
        // insert a record
        cout << "First time using, welcome!\n";
        auto hello_world = bsoncxx::builder::stream::document{} << "init" << "record" << bsoncxx::builder::stream::finalize;
        collection.insert_one(hello_world.view());
    } else {
        cout << "Welcome back\n";
        
        auto collection = db[id];

        auto order_new = bsoncxx::builder::stream::document{} 
            << "created@" << 1 << bsoncxx::builder::stream::finalize;
        auto opts_new = mongocxx::options::find{};
        opts_new.limit(max_new - last_new);
        opts_new.sort(order_new.view());
        auto cursor_new = collection.find(bsoncxx::builder::stream::document{}
                << "type" << "card" 
                << "learning_stage" << open_document
                    << "$lte" << 0 << close_document
                << bsoncxx::builder::stream::finalize, opts_new);
        reload_cards_from_cursor(cursor_new, new_card_list);
        
        auto order_old = bsoncxx::builder::stream::document{} 
            << "due@" << 1 << bsoncxx::builder::stream::finalize;
        auto opts_old = mongocxx::options::find{};
        opts_old.limit(max_review - last_review);
        opts_old.sort(order_old.view()); // (learning_steps.size() + 1)
        auto cursor_old = collection.find(bsoncxx ::builder::stream::document{} 
                << "type" << "card"
                << "learning_stage" << open_document
                    << "$gt" << 0 << close_document
                << "due@" << open_document
                    << "$lte" << (long long int)(end_of_today) << close_document //////////////////
                << bsoncxx::builder::stream::finalize, opts_old);
        reload_cards_from_cursor(cursor_old, review_card_list);

    }
}

vector<card> jobPool::look_up_cards(string front, string back) {
    vector<card> result;
    auto collection = db[id];
    auto order = bsoncxx::builder::stream::document{} 
        << "created@" << -1 << bsoncxx::builder::stream::finalize;
    auto opts = mongocxx::options::find{};
    opts.sort(order.view());
    auto cursor = collection.find(bsoncxx::builder::stream::document{} 
        << "front" << front 
        << "back" << back
        << bsoncxx::builder::stream::finalize, opts);

    reload_cards_from_cursor(cursor, result);
    return result;
}

void jobPool::add_new_card(string front, string back){
    time_t now = time(0);
    stringstream tmp;
    tmp << now;
    auto collection = db[id];
    auto new_record = 
        bsoncxx::builder::stream::document{}
                << "type" << "card" 
                << "front" << front
                << "back" << back
                << "created@" << (long long int)(now) //////////////////
                << "due@" << (long long int)946684800
                << "ease" << 1000.0
                << "learning_stage" << 0
                << "total_study_times" << 0
                << "success_study_times" << 0
                << "interval" << -1.0
                << "id" << front + back + tmp.str()
            << bsoncxx::builder::stream::finalize;
    collection.insert_one(new_record.view());
    update_card_list();
}

bool jobPool::delete_a_card(card &a_card){
    auto collection = db[id];
    bsoncxx::stdx::optional<bsoncxx::document::value> target_in_database =
      collection.find_one(document{} << "id" << a_card.id() << finalize);
    
    if(target_in_database){
        collection.delete_one(target_in_database->view());
        vector<card>::iterator card_in_new_list = find(new_card_list.begin(), new_card_list.end(), a_card);
        vector<card>::iterator card_in_review_list = find(review_card_list.begin(), review_card_list.end(), a_card);
        
        if(card_in_new_list != new_card_list.end()) 
            update_card_list();
        else if(card_in_review_list != review_card_list.end()) 
            update_card_list();
        return true;
    }
    return false;
}
bool jobPool::modify_a_card(card &a_card) {
    if(!delete_a_card(a_card)) return false;

    auto collection = db[id];
    auto new_record = 
        bsoncxx::builder::stream::document{} 
                << "type" << "card" 
                << "front" << a_card.front()
                << "back" << a_card.back()
                << "created@" << (long long)a_card.created_time()
                << "due@" << (long long)a_card.due()
                << "ease" << a_card.ease()
                << "learning_stage" << a_card.learning_stage()
                << "total_study_times" << a_card.total_study_times()
                << "success_study_times" << a_card.success_study_times()
                << "interval" << a_card.interval()
                << "id" << a_card.id()
            << bsoncxx::builder::stream::finalize;
    collection.insert_one(new_record.view());
    update_card_list();
    return true;
}

card* jobPool::get_next_card() {
    if(new_card_list.size() != 0) {
        return &(new_card_list.front());
    }
    if(review_card_list.size() != 0) {
        return &(review_card_list.front());
    }
    return nullptr;
}

bool jobPool::modify_config(config_class which_config, const int& new_max_new, const int& new_max_review, const vector<int>& new_learning_steps) {
    auto collection = db[id];
    
    document filter_buff;
    filter_buff << "type" << "config";
    document update_buffer;
    switch(which_config){
        case(max_new_setting): {
            if(new_max_new < 0) return false;
            if(new_max_new == max_new) return true;
            update_buffer << "$set" << open_document 
                << "max_new" << new_max_new << close_document;
            collection.update_one(filter_buff.view(), update_buffer.view());
            update_config();
            return true;
        }
        case(max_review_setting): {
            if(new_max_review < 0) return false;
            if(new_max_review == max_review) return true;
            update_buffer << "$set" << open_document 
                << "max_review" << new_max_review << close_document;
            collection.update_one(filter_buff.view(), update_buffer.view());
            update_config();
            return true;
        }
        case(learning_steps_setting): {
            if(new_learning_steps.size() < 1) return false;   
            auto array_builder = bsoncxx::builder::basic::array{};
            for (const auto& element : new_learning_steps) {
                if(element < 0) return false;
                array_builder.append(element);
            }
            update_buffer << "$set" << open_document 
                << "learning_steps" << array_builder << close_document;;
            collection.update_one(filter_buff.view(), update_buffer.view());
            update_config();
            return true;
        }
    }
    
    return false;
}

void jobPool::study(card &a_card, performance level) {
    vector<card>::iterator card_in_new_list = find(new_card_list.begin(), new_card_list.end(), a_card);
    vector<card>::iterator card_in_review_list = find(review_card_list.begin(), review_card_list.end(), a_card);
    
    if(card_in_new_list != new_card_list.end()) 
        last_new++;
    else if(card_in_review_list != review_card_list.end()) 
        last_review++;

    // update counter for cards learned
    auto collection = db[id];
    document filter_buff;
    filter_buff << "type" << "config";
    document update_buffer;
    update_buffer << "$set" << open_document 
                << "last_new" << last_new 
                << "last_review" << last_review
                << close_document;
    collection.update_one(filter_buff.view(), update_buffer.view());

    studyService::study(a_card, level, learning_steps);
    modify_a_card(a_card);
    update_card_list();
}


void jobPool::reload_cards_from_cursor(mongocxx::cursor &src, vector<card> &target) {
    target.clear();
    for (auto&& doc : src) {
            bsoncxx::document::element front = doc["front"];
            bsoncxx::document::element back = doc["back"];
            bsoncxx::document::element created = doc["created@"];
            bsoncxx::document::element due = doc["due@"];
            bsoncxx::document::element ease = doc["ease"];
            bsoncxx::document::element learning_stage = doc["learning_stage"];
            bsoncxx::document::element total_study_times = doc["total_study_times"];
            bsoncxx::document::element success_study_times = doc["success_study_times"];
            bsoncxx::document::element interval = doc["interval"];
            bsoncxx::document::element id = doc["id"];

            string card_front, card_back, card_id;
            long long card_created, card_due;
            int card_learning_stage, card_total_study_times, card_success_study_times;
            double card_ease, card_interval;
            
            if(front && front.type() == type::k_utf8) {
                card_front = front.get_utf8().value.to_string();
            }

            if(back && back.type() == type::k_utf8) {
                card_back = back.get_utf8().value.to_string();
            }

            if(created && created.type() == type::k_int64) {
                card_created = created.get_int64().value;
            } 
        
            if(due && due.type() == type::k_int64) {
                card_due = due.get_int64().value;
            }

            if(learning_stage && learning_stage.type() == type::k_int32) {
                card_learning_stage = learning_stage.get_int32().value;
            }

            if(total_study_times && total_study_times.type() == type::k_int32) {
                card_total_study_times = total_study_times.get_int32().value;
            }

            if(success_study_times && success_study_times.type() == type::k_int32) {
                card_success_study_times = success_study_times.get_int32().value;
            }

            if(ease && ease.type() == type::k_double) {
                card_ease = ease.get_double().value;
            }

            if(interval && interval.type() == type::k_double) {
                card_interval = interval.get_double().value;
            }

            if(id && id.type() == type::k_utf8) {
                card_id = id.get_utf8().value.to_string();
            }
            card tmp(
                    time_t(card_created), card_success_study_times,
                    card_total_study_times, card_learning_stage,
                    card_ease, card_front, card_back,
                    card_due, card_interval, card_id
                );
            // cout << tmp;
            target.push_back(tmp);
        }
}


