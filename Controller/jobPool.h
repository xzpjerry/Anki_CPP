//
// Created by Zippo Xie on 2/21/18.
//

#ifndef CARD_ANKI_jobPool_H
#define CARD_ANKI_jobPool_H

#include <iostream>
#include <string>
#include <vector>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>

using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;

#include "../Modal/card.h"
#include "../Service/studyService.h"
using namespace std;


class jobPool {
public:
    jobPool(string username, string password);
    // ~jobPool();

    // card get_current_card(); // get the card with earliest due date
    // card look_up_card(string front, string back);
    // void add_new_card(string front, string back);
    // void delete_a_card(card &a_card); // by passing result from look_up()
    // void edit_a_card(card &a_card, string front, string back);
    // void study();

    // friend ostream &operator<<(ostream &output, const jobPool &A);
private:

    vector<card> card_list;
    int size;
};

#endif //CARD_ANKI_jobPool_H
