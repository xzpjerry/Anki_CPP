//
// Created by Zippo Xie on 2/21/18.
//

#ifndef CARD_ANKI_jobPool_H
#define CARD_ANKI_jobPool_H
#include "../config.h"
#include "../Modal/card.h"
#include <vector>
class jobPool {
public:
    jobPool(vector<card> &input);
    vector<card> get_today_card(int new_amount, int old_amount);
    void get_new_card(int amount, vector<card> &new_list);
    void get_learned_card_for_review(int amount, vector<card> &old_list);
    vector<card> quick_sort(vector<card> list);
    friend ostream &operator<<(ostream &output, const jobPool &A) {
        int tmp = 1;
        output << "Begin to print out the sorted card list for " << A.size << " cards."<< endl;
        for(auto it = A.card_list.begin(); it != A.card_list.end(); ++it) {
            output << "The " << tmp++ << " card:" << endl;
            output << *it;
        }
        return output;
    }
private:
    vector<card> card_list;
    int counter, size;

};

#endif //CARD_ANKI_jobPool_H
