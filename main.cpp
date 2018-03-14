
#include "main.h"

int main() {
    // testing loading userinfo from local file
    if(!jobPool::is_logined()) {
        cout << "Not saved username/password found, cin username, then password";
        string username, password;
        cin >> username >> password; 
        if(jobPool::set_user_credentials_to(username, password))
            cout << "Entered a user's credentials\n"; 
    }
    jobPool test_controller(jobPool::get_credential().at(0),  jobPool::get_credential().at(1));
    
    // test jobPool
    
    cout << "Logined!" << endl;
    cout << test_controller;

    // test modification of config
    cout << "Testing modification of config:\n";
    if(test_controller.modify_config(max_new_setting, 60, -1, {})) {
        cout << "Succeed!\n";
    } else cout << "Cannot modify config\n";

    if(test_controller.modify_config(max_review_setting, -1, 200, {})) {
        cout << "Succeed!\n";
    } else cout << "Cannot modify config\n";

    if(test_controller.modify_config(learning_steps_setting, -1, -1, {60, 300})) {
        cout << "Succeed!\n";
    } else cout << "Cannot modify config\n";


    // test adding new card
    cout << "Testing adding cards; Cin 2 strings:";
    string front, back;
    cin >> front >> back;
    test_controller.add_new_card(front, back);
    cout << "Added" << endl;
    cout << test_controller;

    // test looking up that card
    cout << "Testing looking up the card just added:";
    vector<card> target = test_controller.look_up_cards(front, back);
    if(target.size() != 0) {
        cout << "Found! Here is the first result:\n" << target.front();
    }

    // test get the next card
    cout << "Testing getting the next card: ";
    card* top_card = test_controller.get_next_card();
    if(top_card == nullptr) cout << "No card is availiable for now.\n";
    else {
        cout << "The top card is:" << *top_card;
    }

    // test study a card
    cout << "Testing studying cards; Cin 2 strings(back, front):";
    cin >> front >> back;
    vector<card> target2 = test_controller.look_up_cards(front, back);
    if(target2.size() != 0) {
        test_controller.study(target2.front(), good);
        cout << "Studied!\n";
        cout << test_controller;
    }

    // test change the user
    // When next time you run the program
    // The user will be "New testing username"
    // So, don't forget to run 'make clean' before next time running
    cout << "Changing user now ...\n";
    test_controller.change_to_another_user("New testing username", "New testing password");
    cout << test_controller;


    
    // // test deletion
    // cout << "Testing deleting the card just added:\n";
    // vector<card> target = test_controller.look_up_cards(front, back);
    // if(target.size() != 0) {
    //     cout << "Trying to delete ->" << target.front();
    //     if(test_controller.delete_a_card(target.front()))
    //         cout << "Deleted" << endl;
    //     else
    //         cout << "Deletion failed" << endl;
    // } else {cout << "Cannot find such a card!" << endl;}
    

    return 0;

}