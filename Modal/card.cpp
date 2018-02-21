//
// Created by Zippo Xie on 2/18/18.
//

#include "card.h"


card::card() {
    cout << "Front notes:";
    while(!(cin >> front_)) {
        cout << "Bad value" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Type again" << endl;
        cout << "Front notes:";
    }
    cout << "Back notes:";
    while(!(cin >> back_)) {
        cout << "Bad value" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Type again" << endl;
        cout << "Back notes:";
    }
    creadted_time_ = time(0);
    ease_ = 1000;
    learning_stage_ = -LEARN_RELEARN_STEPS;
    //learning_stage_ = 0;
    total_study_times_ = 0;
    success_study_times_ = 0;
    interval_ = -1;
    stringstream tmp;
    tmp << creadted_time_;
    id_ = front_ + tmp.str();
}

card::card(time_t ct, double sst, double tst, short ls, double e, string f, string b, time_t d, double i){
    creadted_time_ = ct;
    success_study_times_ = sst;
    total_study_times_ = tst;
    learning_stage_ = ls;
    ease_ = e;
    front_ = f;
    back_ = b;
    due_ = d;
    interval_ = i;
    stringstream tmp;
    tmp << creadted_time_;
    id_ = front_ + tmp.str();
}
