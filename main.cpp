#include "Modal/card.h"
#include "Service/studyService.h"
#include "Service/saveLoad.h"

int main() {

    vector<card> cardList;
    card c2(0, 0, 0, 0, .35469, "this is the front", "this is the back", 0, 0);

    save(c2);
    load(cardList);
    cout << cardList[0].front() << endl;
    cout << cardList[0].back() << endl;
    cout << "ease: " << cardList[0].ease() << endl;

//    card test;
//    while(1){
//        studyService::study(test, good);
//        sleep(1);
//    }

    return 0;

}