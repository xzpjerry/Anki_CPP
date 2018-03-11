//
// Created by Zippo Xie on 3/8/18.
//

#include "config.h"

//setters
bool Config::set_user_info(string username, string passwd) {
    ofstream file;
    file.open("config.txt");
    if(!file.is_open())
        return false;
    std::hash <string> hash;
    unsigned long hashedUserName = hash(username);
    unsigned long hashedPasswd = hash(passwd);

    file << ":USERNAME:" << hashedUserName << endl;
    file << ":USERPASSWD:" << hashedPasswd << endl;
    file << ":end:" << endl;
    return true;
}

//getters
bool Config::get_user_info(string &username, string &passwd) {
    ifstream file;
    file.open("config.txt");
    if(!file.is_open())
        return false;

    string line;
    stringstream stre_name, stre_pass;
    unsigned long tmp;
    while(!file.eof()){
        getline(file, line, ':');
        if(line == "USERNAME") {
            file >> tmp;
            stre_name << tmp;
            stre_name >> username;
        }
        else if(line == "USERPASSWD") {
            file >> tmp;
            stre_pass << tmp;
            stre_pass >> passwd;
        }
        if(line == "end") {
            file.close();
        }
    }
    return true;

}