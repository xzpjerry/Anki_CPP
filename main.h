//
// Created by Zippo Xie on 2/20/18.
//

#ifndef CARD_ANKI_MAIN_H
#define CARD_ANKI_MAIN_H
#include <iostream>
#include <mongocxx/instance.hpp>
mongocxx::instance instance{};// don't put inside main 

#include "Modal/card.h"
#include "Controller/jobPool.h"
#endif //CARD_ANKI_MAIN_H
