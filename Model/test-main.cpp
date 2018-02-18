#include "card.hpp"
#include <unistd.h>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>

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

int main() {

    vector<card> cardList;
    card c2(0, 0, 0, 0, .35469, "this is the front", "this is the back", 0, 0);

    save(c2);
    load(cardList);
    cout << cardList[0].front() << endl;
    cout << cardList[0].back() << endl;
    cout << "ease: " << cardList[0].ease() << endl;

    card test;
    while(1){
        studyService::study(test, good);
        sleep(1);
    }

    return 0;

}