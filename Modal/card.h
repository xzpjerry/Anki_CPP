//
// Created by Zippo Xie on 2/18/18.
//

#ifndef CARD_ANKI_CARD_H
#define CARD_ANKI_CARD_H

#include <string>
#include <time.h>
#include <sstream>
#include <iostream>
using namespace std;
<<<<<<< HEAD
#include "../Service/config.h"
=======
>>>>>>> Dev_mongodb_based

class card {
public:
    friend class studyService;
    card(time_t ct, int sst, int tst, int ls, double e, string f, string b, time_t d, double i, string id);

    friend bool operator== ( const card &n1, const card &n2);
    friend ostream &operator<<(ostream &output, const card &A);

    time_t created_time() const{return created_time_;}
    int success_study_times() const{return success_study_times_;}
    int total_study_times() const{return total_study_times_;}
    int learning_stage() const{return learning_stage_;}
    double ease() const{return ease_;}
    string front() const{return front_;}
    string back() const{return back_;}
    time_t due() const{return due_;}
    double interval() const{return interval_;}
    string id() const{return id_;}

private:
    string front_, back_, id_;
    time_t created_time_, due_;;
    int success_study_times_, total_study_times_, learning_stage_;
    double ease_, interval_;

    
};


#endif //CARD_ANKI_CARD_H
