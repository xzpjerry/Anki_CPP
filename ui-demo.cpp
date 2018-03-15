#include "ui-demo.h"

int main() {
	if (!jobPool::is_logined()) {
		cout << "Enter a username and password";
		string uname, pword;
		cin >> uname >> pword;
		if(jobPool::set_user_credentials_to(uname, pword))
            cout << "Entered a user's credentials\n";
	}
	// "activates" the ui - clears the screen and captures input
	UI* ui = new UI();
	jobPool deck(jobPool::get_credential().at(0), jobPool::get_credential().at(1));

	while(1) {
		int mode = ui->present_menu();
		if (mode == 0) {
			while(1) {
				card* c = deck.get_next_card();
				performance result = ui->present_card(c);

				if (result == unf) {
					break;
				}

				deck.study((*c), result);
			}
		}
		else if (mode == 1) {
			// open create panel
		}
		else if (mode == 2) {
			break;
		}
	}
	
	// this is important to allow the program to cleanly exit & allow the terminal to behave normally after termination
	delete ui;
}
