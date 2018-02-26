#include "Modal/card.h"
#include "Service/studyService.h"
#include "Service/saveLoad.h"
#include "Controller/jobPool.h"

int main() {

    vector<card> cardList;
    card c2(time(0), 0, 0, 0, .35469, "this is the front", "this is the back", 0, 0);

    save(c2);
    load(cardList);
    cout << cardList[0];

    card test;
    while(1){
        cout << test;
        int tmp;
        cout << "Input performance (0:bad, 1:hard, 2:good, 3:easy):";
        cin >> tmp;
        studyService::study(test, static_cast<performance>(tmp));
        cardList.push_back(test);
        jobPool sort_test(cardList);
        cout << sort_test;
        sleep(1);
    }

    return 0;

}