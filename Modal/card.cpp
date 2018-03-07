//
// Created by Zippo Xie on 2/18/18.
//

#include "card.h"

card::card(time_t ct, int sst, int tst, int ls, double e, string f, string b, time_t d, double i, string id){
    created_time_ = ct;
    success_study_times_ = sst;
    total_study_times_ = tst;
    learning_stage_ = ls;
    ease_ = e;
    front_ = f;
    back_ = b;
    due_ = d;
    interval_ = i;
    stringstream tmp;
    tmp << created_time_;
    id_ = id;
}
bool operator== ( const card &n1, const card &n2) {
    return n1.id_ == n2.id_;
}
ostream &operator<<(ostream &output, const card &A) {
    
    output << "**************" << endl;
    output << "Id:" << A.id_ << endl;
    output << "Front:" << A.front_ << endl;
    output << "Back:" << A.back_ << endl;
    output << "Seconds since 1970: " << A.created_time_ << endl;
    output << "Creadted on: " << ctime(&A.created_time_);
    output << "Ease:" << A.ease_ << endl;
    output << "Stage:" << A.learning_stage_ << endl;
    output << "Total study times:" << A.total_study_times_ << endl;
    output << "Successful study times:" << A.success_study_times_ << endl;
    output << "Next due day is on: " << ctime(&A.due_);
    output << "Interval: " << A.interval_ << endl;
    output << "**************" << endl;
    return output;
}
