//
// Created by Zippo Xie on 2/21/18.
//
#include "jobPool.h"

jobPool::jobPool() {
    load(card_list);
    size = static_cast<int>(card_list.size());
    card_list = quick_sort(card_list);
}

jobPool::~jobPool() {
    for(auto it = card_list.begin(); it != card_list.end(); ++it)
        save(*it);

    // and then save configs
}

card jobPool::get_current_card() { // get the card with earliest due date
    if(card_list.size() == 0){
        auto default_card_str = "DEFAULT_NOT_CARDS_AVAILABLE";
        string default_info(default_card_str);
        return card(default_info, default_info);
    }
    return card_list.front();
}
//card jobPool::look_up_card(string front, string back){
//
//}
void jobPool::add_new_card(string front, string back){
    card_list.push_back(card(front, back));
    size++;
}
void jobPool::delete_a_card(card &a_card){
    vector<card>::iterator card_in_list = find(card_list.begin(), card_list.end(), a_card);
    if(card_in_list != card_list.end()) {
        // need saveLoad's API
    }
}
void jobPool::edit_a_card(card &a_card, string front, string back){

}

void jobPool::study(card &a_card, performance level) {
    vector<card>::iterator card_in_list = find(card_list.begin(), card_list.end(), a_card);
    if(card_in_list != card_list.end()) {
        studyService::study(*card_in_list, level);

        time_t end_of_today, now;
        now = time(0);
        tm* tm = localtime(&now);
        tm->tm_hour = 0;
        tm->tm_min = 0;
        tm->tm_sec = 0;
        tm->tm_mday ++;
        end_of_today = mktime(tm);

        if((*card_in_list).due() > end_of_today) { // the card is not today's assignment then
            card_list.erase(card_in_list);
        } else quick_sort(card_list);
    }
}

vector<card> jobPool::quick_sort(vector<card> list) {
    if(list.size() < 2) return list;
    vector<card> card_tmp_list_small; // for sorting use
    vector<card> card_tmp_list_big;
    vector<card> card_tmp_list_same;
    card pivot = list.at(0);

    for(auto it = list.begin(); it != list.end(); ++it) {
        if((*it).due() < (pivot.due())) card_tmp_list_small.push_back((*it));
        else if((*it).due() > (pivot.due())) card_tmp_list_big.push_back((*it));
        else card_tmp_list_same.push_back((*it));
    }

    vector<card> result_small = quick_sort(card_tmp_list_small);
    vector<card> result_big = quick_sort(card_tmp_list_big);
    vector<card> result;
    result.reserve(result_small.size() + card_tmp_list_same.size() + result_big.size());
    result.insert(result.end(), result_small.begin(), result_small.end());
    result.insert(result.end(), card_tmp_list_same.begin(), card_tmp_list_same.end());
    result.insert(result.end(), result_big.begin(), result_big.end());
    return result;
}

ostream &operator<<(ostream &output, const jobPool &A) {
    int tmp = 1;
    output << "Begin to print out the sorted card list for " << A.size << " cards."<< endl;
    for(auto it = A.card_list.begin(); it != A.card_list.end(); ++it) {
        output << "The " << tmp++ << " card:" << endl;
        output << *it;
    }
    return output;
}

