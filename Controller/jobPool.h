//
// Created by Zippo Xie on 2/21/18.
//

#ifndef CARD_ANKI_jobPool_H
#define CARD_ANKI_jobPool_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <bsoncxx/types.hpp>

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::type;

enum config_class {max_new_setting, max_review_setting, learning_steps_setting};

#include "../Modal/card.h"
#include "../Service/studyService.h"
using namespace std;


class jobPool {
public:
    jobPool(string username, string password);
    
    // for view's usage:
    card* get_next_card(); 
    vector<card> look_up_cards(string front, string back);
    void add_new_card(string front, string back);
    bool delete_a_card(card &a_card); // by passing result from look_up()
    bool modify_config(config_class which_config, 
        const int& new_max_new, const int& new_max_review, const vector<int>& new_learning_steps);
    void study(card &a_card, performance level);
    
    friend ostream &operator<<(ostream &output, const jobPool &A);
private:
    void update_card_list();
    void update_config();
    bool modify_a_card(card &a_card);
    void reload_cards_from_cursor(mongocxx::cursor &src, vector<card> &target);
    string id;
    mongocxx::client conn{mongocxx::uri{"mongodb://bot:53744D9E-0C0B-4298-851A-AEB56ECE58F7@ds139984.mlab.com:39984/cis330"}};
    mongocxx::database db = conn["cis330"];
    vector<card> new_card_list, review_card_list;
    vector<int> learning_steps;
    int max_new, last_new, max_review, last_review;
    time_t last_studied;
};

#endif //CARD_ANKI_jobPool_H
