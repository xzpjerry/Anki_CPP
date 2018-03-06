#include "ui.hpp"
#include "../Modal/card.h"

int main() {
	// draws the UI - will draw the menu once that is done, for now just clears the screen
	UI* ui = new UI();

	// make a test card to display
	card* c = new card("front side","back side");
	
	//presents the card on-screen, this returns an indicating how proficient the user feels about the card
	ui->present_card(c);
	
	// this is important to allow the program to cleanly exit & allow the terminal to behave normally after termination
	delete ui;
}
