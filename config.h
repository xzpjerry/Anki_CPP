//
// Created by Zippo Xie on 2/20/18.
//

#ifndef CARD_ANKI_CONFIG_H
#define CARD_ANKI_CONFIG_H

#include <string>
#include <sstream>
#include <iostream>

#include <limits>
#include <unistd.h>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum performance {bad, hard, good, easy};

// The following parameters should be read from a config file
#define LEARN_RELEARN_STEPS 2
static int learning_interval[LEARN_RELEARN_STEPS] = {60, 600};
#endif //CARD_ANKI_CONFIG_H
