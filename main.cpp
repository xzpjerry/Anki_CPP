
#include "main.h"

int main() {
    // testing loading userinfo from local file
    string username, password;
    if(!Config::get_user_info(username, password)) {
        cout << "Not saved username/password found, cin username, then password";
        cin >> username >> password;
        Config::set_user_info(username, password);
        Config::get_user_info(username, password);
    }
    
    // test jobPool
    jobPool test2(username, password);
    cout << "Logined!" << endl;
    cout << test2;

    // test modification of config
    cout << "Testing modification of config:\n";
    if(test2.modify_config(max_new_setting, 60, -1, {})) {
        cout << "Succeed!\n";
    } else cout << "Cannot modify config\n";

    if(test2.modify_config(max_review_setting, -1, 200, {})) {
        cout << "Succeed!\n";
    } else cout << "Cannot modify config\n";

    if(test2.modify_config(learning_steps_setting, -1, -1, {60, 300})) {
        cout << "Succeed!\n";
    } else cout << "Cannot modify config\n";


    // test adding new card
    cout << "Testing adding cards; Cin 2 strings:";
    string front, back;
    cin >> front >> back;
    test2.add_new_card(front, back);
    cout << "Added" << endl;
    cout << test2;

    // test looking up that card
    cout << "Testing looking up the card just added:";
    vector<card> target = test2.look_up_cards(front, back);
    if(target.size() != 0) {
        cout << "Found! Here is the first result:\n" << target.front();
    }

    // test get the next card
    cout << "Testing getting the next card: ";
    card* top_card = test2.get_next_card();
    if(top_card == nullptr) cout << "No card is availiable for now.\n";
    else {
        cout << "The top card is:" << *top_card;
    }

    // test study a card
    cout << "Testing studying cards; Cin 2 strings(back, front):";
    cin >> front >> back;
    vector<card> target2 = test2.look_up_cards(front, back);
    if(target2.size() != 0) {
        test2.study(target2.front(), good);
        cout << "Studied!\n";
        cout << test2;
    }


    
    // // test deletion
    // cout << "Testing deleting the card just added:\n";
    // vector<card> target = test2.look_up_cards(front, back);
    // if(target.size() != 0) {
    //     cout << "Trying to delete ->" << target.front();
    //     if(test2.delete_a_card(target.front()))
    //         cout << "Deleted" << endl;
    //     else
    //         cout << "Deletion failed" << endl;
    // } else {cout << "Cannot find such a card!" << endl;}
    

    return 0;

}