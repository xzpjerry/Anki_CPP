//
// Created by Zippo Xie on 2/18/18.
//

#ifndef CARD_ANKI_STUDYSERVICE_H
#define CARD_ANKI_STUDYSERVICE_H

#include "../config.h"
#include "../Modal/card.h"

class studyService {
public:
    static void study(card &a_card, performance level);
private:
    static double next_interval(card &a_card, performance level);
    static void learn_relearn(card &a_card, performance level);
    static void review(card &a_card, performance level);
};

#endif //CARD_ANKI_STUDYSERVICE_H
