//
// Created by Zippo Xie on 2/18/18.
//

#ifndef CARD_ANKI_SAVELOAD_H
#define CARD_ANKI_SAVELOAD_H
#include <limits>
#include <unistd.h>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include "../config.h"
#include "../Modal/card.h"
void save(const card& obj);
void load(vector<card> &cardList);
#endif //CARD_ANKI_SAVELOAD_H
