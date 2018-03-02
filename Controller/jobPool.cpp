//
// Created by Zippo Xie on 2/21/18.
//
#include "jobPool.h"

jobPool::jobPool(string username, string password) {
    mongocxx::client conn{mongocxx::uri{"mongodb://bot:53744D9E-0C0B-4298-851A-AEB56ECE58F7@ds139984.mlab.com:39984/cis330"}};
    mongocxx::database db = conn["cis330"];
    auto collection = db[username+password];

    // insert a record
    auto hello_world = bsoncxx::builder::stream::document{} << "hello" << "world" << bsoncxx::builder::stream::finalize;
    collection.insert_one(hello_world.view());

    auto order = bsoncxx::builder::stream::document{} << "created@" << -1 << bsoncxx::builder::stream::finalize;
    std::cout << "Finding every record\n";
    auto opts = mongocxx::options::find{};
    opts.sort(order.view());
    auto cursor = collection.find({}, opts);

    for (auto&& doc : cursor) {
        
        cout << doc["hello"] << endl;

        // iterate over the elements in a bson document
        for (bsoncxx::document::element ele : doc) {
            // element is non owning view of a key-value pair within a document.

            // we can use the key() method to get a string_view of the key.
            bsoncxx::stdx::string_view field_key{ele.key()};

            std::cout << "Got key, key = " << field_key << std::endl;

            // we can use type() to get the type of the value.
            switch (ele.type()) {
                case bsoncxx::type::k_utf8:
                    std::cout << "Got String!" << std::endl;
                    cout << bsoncxx::to_json(doc) << endl;
                    break;
                case bsoncxx::type::k_oid:
                    std::cout << "Got ObjectId!" << std::endl;
                    break;
                case bsoncxx::type::k_array: {
                    std::cout << "Got Array!" << std::endl;
                    // if we have a subarray, we can access it by getting a view of it.
                    bsoncxx::array::view subarr{ele.get_array().value};
                    for (bsoncxx::array::element ele : subarr) {
                        auto MyString = ele.get_utf8().value.to_string();
                        cout << MyString;
                    }
                    break;
                }
                default:
                    std::cout << "We messed up!" << std::endl;
            }

            // usually we don't need to actually use a switch statement, because we can also
            // get a variant 'value' that can hold any BSON type.
            bsoncxx::types::value ele_val{ele.get_value()};
        }
    }
    cout << "QUery done\n\n";


    // size = static_cast<int>(card_list.size());
    // card_list = quick_sort(card_list);
}

// jobPool::~jobPool() {
//     for(auto it = card_list.begin(); it != card_list.end(); ++it)
//         save(*it);

//     // and then save configs
// }

// card jobPool::get_current_card() { // get the card with earliest due date
//     if(card_list.size() == 0){
//         auto default_card_str = "DEFAULT_NOT_CARDS_AVAILABLE";
//         string default_info(default_card_str);
//         return card(default_info, default_info);
//     }
//     return card_list.front();
// }
// //card jobPool::look_up_card(string front, string back){
// //
// //}
// void jobPool::add_new_card(string front, string back){
//     card_list.push_back(card(front, back));
//     size++;
// }
// void jobPool::delete_a_card(card &a_card){
//     vector<card>::iterator card_in_list = find(card_list.begin(), card_list.end(), a_card);
//     if(card_in_list != card_list.end()) {
//         // need saveLoad's API
//     }
// }
// void jobPool::edit_a_card(card &a_card, string front, string back){

// }

// void jobPool::study(card &a_card, performance level) {
//     vector<card>::iterator card_in_list = find(card_list.begin(), card_list.end(), a_card);
//     if(card_in_list != card_list.end()) {
//         studyService::study(*card_in_list, level);

//         time_t end_of_today, now;
//         now = time(0);
//         tm* tm = localtime(&now);
//         tm->tm_hour = 0;
//         tm->tm_min = 0;
//         tm->tm_sec = 0;
//         tm->tm_mday ++;
//         end_of_today = mktime(tm);

//         if((*card_in_list).due() > end_of_today) { // the card is not today's assignment then
//             card_list.erase(card_in_list);
//         } else quick_sort(card_list);
//     }
// }

// vector<card> jobPool::quick_sort(vector<card> list) {
//     if(list.size() < 2) return list;
//     vector<card> card_tmp_list_small; // for sorting use
//     vector<card> card_tmp_list_big;
//     vector<card> card_tmp_list_same;
//     card pivot = list.at(0);

//     for(auto it = list.begin(); it != list.end(); ++it) {
//         if((*it).due() < (pivot.due())) card_tmp_list_small.push_back((*it));
//         else if((*it).due() > (pivot.due())) card_tmp_list_big.push_back((*it));
//         else card_tmp_list_same.push_back((*it));
//     }

//     vector<card> result_small = quick_sort(card_tmp_list_small);
//     vector<card> result_big = quick_sort(card_tmp_list_big);
//     vector<card> result;
//     result.reserve(result_small.size() + card_tmp_list_same.size() + result_big.size());
//     result.insert(result.end(), result_small.begin(), result_small.end());
//     result.insert(result.end(), card_tmp_list_same.begin(), card_tmp_list_same.end());
//     result.insert(result.end(), result_big.begin(), result_big.end());
//     return result;
// }

// ostream &operator<<(ostream &output, const jobPool &A) {
//     int tmp = 1;
//     output << "Begin to print out the sorted card list for " << A.size << " cards."<< endl;
//     for(auto it = A.card_list.begin(); it != A.card_list.end(); ++it) {
//         output << "The " << tmp++ << " card:" << endl;
//         output << *it;
//     }
//     return output;
// }

