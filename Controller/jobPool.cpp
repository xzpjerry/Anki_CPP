//
// Created by Zippo Xie on 2/21/18.
//
#include "jobPool.h"

jobPool::jobPool(vector<card> &input) : counter(0), size(input.size()) {
    card_list = quick_sort(input);
    input.clear();
    input = card_list;
}
//vector<card> jobPool::get_today_card(int new_amount, int old_amount) {
//    vector<card> result, new_list, old_list;
//    result.reserve(static_cast<unsigned long>(new_amount + old_amount));
//    get_new_card(new_amount, new_list);
//    get_learned_card_for_review(old_amount, old_list);
//    result.insert(result.end(), new_list.begin(), new_list.end());
//    result.insert(result.end(), old_list.begin(), old_list.end());
//    return result;
//}
//void jobPool::get_new_card(int amount, vector<card> &new_list) {
//    for(auto it = card_list.begin(); it != card_list.end(); ++it) {
//        if((*it).learning_stage() > 0) break;
//        new_list.push_back(*it);
//    }
//}
//void jobPool::get_learned_card_for_review(int amount, vector<card> &old_list) {
//    for(auto it = card_list.begin(); it != card_list.end(); ++it) {
//        if((*it).learning_stage() < 0) continue;
//        old_list.push_back(*it);
//    }
//}
vector<card> jobPool::quick_sort(vector<card> list) {
    if(list.size() < 2) return list;
    vector<card> card_tmp_list_small; // for sorting use
    vector<card> card_tmp_list_big;
    vector<card> card_tmp_list_same;
    card pivot = list.at(0);
    counter++;
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


