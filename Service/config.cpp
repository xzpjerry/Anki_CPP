#include "config.h"
#include <fstream>
#include <iostream>
using namespace std;

Config::Config() : learning_intervals_(2) {
	this->loadConfig();
}
Config::~Config(){
	this->saveConfig();
}

void Config::saveConfig(){
	ofstream file;
    file.open("config.txt");

    file << ":MAX_NEW_CARDS:" << this->get_MAX_NEW_CARDS() << endl;
    file << ":MAX_REVIEWS:" << this->get_MAX_REVIEWS() << endl;
    file << ":learning_intervals:" << this->get_learning_intervals()[0] << "\n" << this->get_learning_intervals()[1] << endl;
    file << ":end:" << endl;
}

void Config::loadConfig(){
	int mnc, mr, li0, li1;
    //string up;
    vector<int> learning_intervals;

    ifstream file("config.txt");
    if (file.fail()){ // set values to default value
        cout << "no config.txt" << endl;
        this->MAX_NEW_CARDS_ = 20;
        this->MAX_REVIEWS_ = 600;
        this->learning_intervals_[0] = 60;
        this->learning_intervals_[1] = 600;
    }else{
        string line;
        while (!file.eof()){
            getline(file, line, ':');

            if (line=="MAX_NEW_CARDS")
                file >> mnc;
            if (line=="MAX_REVIEWS")
                file >> mr;
            if (line=="learning_intervals"){
                file >> li0;
                file >> li1;
            }
            //if (line == "userPass")
                //file >> up;
            if (line=="end"){  
            	this->MAX_NEW_CARDS_ = mnc;  
                this->MAX_REVIEWS_ = mr;
                //this->userPass = up;
                this->learning_intervals_[0] = li0;
                this->learning_intervals_[1] = li1;
                file.close();
            }
        }
    }
}

void Config::set_MAX_NEW_CARDS(int i){
 	this->MAX_NEW_CARDS_ = i; 
 	saveConfig();
 };

void Config::set_MAX_REVIEWS(int i){
    this->MAX_REVIEWS_ = i; 
    saveConfig();
 };

 void Config::set_learning_intervals(int i, int j){
 	this->learning_intervals_[0] = i;
    this->learning_intervals_[1] = j; 
 	saveConfig();
 };