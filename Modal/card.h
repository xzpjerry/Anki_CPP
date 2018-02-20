//
// Created by Zippo Xie on 2/18/18.
//

#ifndef CARD_ANKI_CARD_H
#define CARD_ANKI_CARD_H

#include "../config.h"

class card {
public:
    friend class studyService;
    card();
    card(time_t ct, double sst, double tst, short ls, double e, string f, string b, time_t d, double i);


    friend ostream &operator<<(ostream &output, const card &A) {
        char *verbose = ctime(&A.creadted_time_);
        output << "**************" << endl;
        output << "Id:" << A.id() << endl;
        output << "Front:" << A.front() << endl;
        output << "Back:" << A.back() << endl;
        output << "Seconds since 1970: " << A.creadted_time_ << endl;
        output << "Creadted on: " << verbose;
        output << "Ease:" << A.ease() << endl;
        output << "Stage:" << A.learning_stage() << endl;
        output << "Total study times:" << A.total_study_times() << endl;
        output << "Successful study times:" << A.success_study_times() << endl;
        verbose = ctime(&A.due_);
        output << "Next due day is on: " << verbose;
        output << "**************" << endl;
        return output;
    }
    time_t creadted_time() const{return creadted_time_;}
    double success_study_times() const{return success_study_times_;}
    double total_study_times() const{return total_study_times_;}
    short learning_stage() const{return learning_stage_;}
    double ease() const{return ease_;}
    string front() const{return front_;}
    string back() const{return back_;}
    time_t due() const{return due_;}
    double interval() const{return interval_;}
    string id() const{return id_;}
private:
    time_t creadted_time_;
    double success_study_times_;
    double total_study_times_;
    short learning_stage_;
    double ease_;
    string front_;
    string back_;
    time_t due_ = 0;
    double interval_ = -1;
    string id_;
};


#endif //CARD_ANKI_CARD_H
