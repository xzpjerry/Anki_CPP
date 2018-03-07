//
// Created by Zippo Xie on 2/18/18.
//

#ifndef CARD_ANKI_STUDYSERVICE_H
#define CARD_ANKI_STUDYSERVICE_H

#include <vector>
#include <algorithm>
using namespace std;
#include "../Modal/card.h"
enum performance {bad, hard, good, easy};

class studyService {
public:
    static void study(card &a_card, performance level, const vector<int>& learning_steps);
private:
    static double next_interval(card &a_card, performance level, const vector<int>& learning_steps);
    static void learn_relearn(card &a_card, performance level, const vector<int>& learning_steps);
    static void review(card &a_card, performance level);
};

#endif //CARD_ANKI_STUDYSERVICE_H
