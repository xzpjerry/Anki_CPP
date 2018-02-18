//
// Created by Zippo Xie on 2/18/18.
//
#include "saveLoad.h"
void save(const card& obj) {
    ofstream file;
    file.open("save.txt", ios::app);

    file << ":creadted_time:" << obj.creadted_time() << endl;
    file << ":success_study_times:" << obj.success_study_times() << endl;
    file << ":total_study_times:" << obj.total_study_times() << endl;
    file << ":learning_stage:" << obj.learning_stage() << endl;
    file << ":ease:" << obj.ease() << endl;
    file << ":front:" << obj.front() << endl;
    file << ":back:" << obj.back() << endl;
    file << ":due:" << obj.due() << endl;
    file << ":interval:" << obj.interval() << endl;
    file << ":end:" << endl;
}

void load(vector<card> &cardList) {
    time_t creadted_time, due;
    double success_study_times, total_study_times, ease, interval;
    short learning_stage;
    string front, back;

    ifstream file;
    string line;

    file.open("save.txt");

    while (!file.eof())
    {
        getline(file, line, ':');


        if (line=="creadted_time")
            file >> creadted_time;
        if (line=="success_study_times")
            file >> success_study_times;
        if (line=="total_study_times")
            file >> total_study_times;
        if (line=="learning_stage")
            file >> learning_stage;
        if (line=="ease")
            file >> ease;
        if (line=="front")
            getline(file, front);
        if (line=="back")
            getline(file, back);
        if (line=="due")
            file >> due;
        if (line=="interval")
            file >> interval;
        if (line=="end"){
            card c(creadted_time, success_study_times, total_study_times, learning_stage, ease, front, back, due, interval);
            cardList.push_back(c);
        }
    }
}
