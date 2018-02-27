//
// Created by Zippo Xie on 2/21/18.
//

#ifndef CARD_ANKI_jobPool_H
#define CARD_ANKI_jobPool_H

#include <iostream>
#include <vector>
using namespace std;
#include "../Modal/card.h"
#include "../Service/saveLoad.h"
#include "../Service/studyService.h"

class jobPool {
public:
    jobPool();
    ~jobPool();

    card get_current_card(); // get the card with earliest due date
//    card look_up_card(string front, string back);
    void add_new_card(string front, string back);
    void delete_a_card(card &a_card);
    void edit_a_card(card &a_card, string front, string back);

    void study(card &a_card, performance level);

    friend ostream &operator<<(ostream &output, const jobPool &A);
private:
    vector<card> quick_sort(vector<card> list); // sort by due date

    vector<card> card_list;
    int size;
};

#endif //CARD_ANKI_jobPool_H
