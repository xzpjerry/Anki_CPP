#include "Modal/card.h"
#include "Controller/jobPool.h"

int main() {

    jobPool instance;
//    string front, back;
//    cout << "Enter test card front:";
//    cin >> front;
//    cout << "Enter test card back:";
//    cin >> back;
//    card test(front, back);
//    cout << test;

    while(1){
        int tmp;
        card current = instance.get_current_card();
        cout << "Current @ " << current;
        cout << "Input performance (0:bad, 1:hard, 2:good, 3:easy):";
        cin >> tmp;
        instance.study(current, static_cast<performance>(tmp));

        cout << instance;
        sleep(1);
    }

    return 0;

}