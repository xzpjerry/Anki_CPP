#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
using namespace std;

class Config{
public:
    //setters
    static bool set_user_info(string username, string passwd);

    //getters
    static bool get_user_info(string &username, string &passwd);
};

#endif //CONFIG_H