#include "main.h"

int main() {

    // test card modal
    cout << "Testing card modal, cin 2 strings:";
    string front, back;
    cin >> front >> back;
    card test(front, back);
    cout << test;

    // test jobPool
    cout << "Testing jobPool, cin username, then password";
    string username, password;
    cin >> username >> password;
    jobPool test2(username, password);
    

    return 0;

}