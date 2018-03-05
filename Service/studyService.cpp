//
// Created by Zippo Xie on 2/18/18.
//

#include "studyService.h"

void studyService::study(card &a_card, performance level) {
//    cout << a_card;
    if(a_card.learning_stage() < 0 || level == bad) learn_relearn(a_card, level);
    else review(a_card, level);
//    cout << a_card;
}

double studyService::next_interval(card &a_card, performance level) {
    if(a_card.learning_stage() < 0 || level == bad) { // learning or relearn stage
        if(a_card.learning_stage() < -config.get_LEARN_RELEARN_STEPS() || level == bad) {return -1;} // Need to be reseted
        return config.get_learning_intervals()[config.get_LEARN_RELEARN_STEPS() + a_card.learning_stage()];
    } else { // learned stage
        double interval = a_card.interval();
        double ease = a_card.ease();
        double d = (time(0) - a_card.creadted_time())/60;
        double hard_interval = ((interval + 86400) > (interval + d/4)) ? (interval + 86400) : (interval + d/4);
        if(level == hard) {return hard_interval;}

        double reease = ease/1000;
        double good_interval = ((hard_interval + 86400) > ((interval + d/2)*reease)) ? (hard_interval + 86400) : ((interval + d/2)*reease);
        if(level == good) {return good_interval;}

        double easey_interval = ((good_interval + 86400) > ((interval + d)*reease)) ? (good_interval + 86400) : ((interval + d)*reease);
        return easey_interval;
    }
}
void studyService::learn_relearn(card &a_card, performance level) {
    cout << "Learning stage @ " << a_card.learning_stage() << endl;

    double new_interval = a_card.interval();
    a_card.total_study_times_++;
    if(level != bad) {
        if(a_card.learning_stage() == 0) { // last stage of learning; will enter review stage next time
            a_card.interval_ = (86400 > new_interval) ? 86400 : new_interval; // max(1day, calculted_interval)
        }
        else {
            new_interval = next_interval(a_card, level);
            if(new_interval == -1)  { // reset
                a_card.learning_stage_ = -config.get_LEARN_RELEARN_STEPS();
                new_interval = 60;
            }
        }
        a_card.success_study_times_++;
        a_card.learning_stage_++;
    }
    else {
        a_card.learning_stage_ = -config.get_LEARN_RELEARN_STEPS();
        new_interval = 60;
        a_card.ease_ = (100 > (a_card.ease() - 200)) ? 100 : (a_card.ease() - 200);
    }
    a_card.due_ = static_cast<time_t>(time(0) + new_interval);
}
void studyService::review(card &a_card, performance level) {
    a_card.total_study_times_++;
    a_card.success_study_times_++;
    if(level == hard) a_card.ease_ = (100 > (a_card.ease() - 100)) ? 100 : (a_card.ease() - 100);
    else if(level == easy) a_card.ease_ = (1500 < (a_card.ease() + 200)) ? 1500 : (a_card.ease() + 200);

    double new_interval = next_interval(a_card, level);
    a_card.interval_ = new_interval;
    a_card.due_ = time(0) + new_interval;
}