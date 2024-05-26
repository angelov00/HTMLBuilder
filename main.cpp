#include "HTMLDocumentManager.hpp"

int main() {

	HTMLDocumentManager manager;

	const std::string welcomeMessage = "Welcome!\nWhat do you want to do today? Please enter one of the following:\n\t1. Create a new website	\n\t2. Edit an existing website";
	std::cout << welcomeMessage << std::endl;

	short choice;
	std::cin >> choice;
	if (choice == 1) {
		manager.build();
	} else if(choice == 2) {
		manager.edit();
	}

	return 0;
}