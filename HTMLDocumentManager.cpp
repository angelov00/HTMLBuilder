#include "HTMLDocumentManager.hpp"

HTMLElement* HTMLDocumentManager::createElement(short choice) {
	switch (choice) {
		case 1: return ElementFactory::createElement(ElementType::HEADING);
		case 2: return ElementFactory::createElement(ElementType::PARAGRAPH);
		case 3: return ElementFactory::createElement(ElementType::IMAGE);
		case 4: return ElementFactory::createElement(ElementType::HYPERLINK);
		case 5: return ElementFactory::createElement(ElementType::NEW_LINE);
		case 6: return ElementFactory::createElement(ElementType::HORIZONTAL_LINE);
		default: std::cout << "Invalid choice! Try again!" << std::endl; return nullptr;
		break;
	}
}

HTMLHead HTMLDocumentManager::buildHTMLHead() {
	std::string title;
	std::cout << "Please enter a title for your website:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, title);

	std::cout << "Do you want to set favicon of the site. (Y/N)" << std::endl;
	char c;
	std::cin >> c;

	std::string faviconURL = "";
	if (c == 'Y' || c == 'y') {
		std::cout << "Please provide favicon URL: " << std::endl;
		std::cin.ignore();
		std::getline(std::cin, faviconURL);
	}

	std::cout << "We are now building " << title << std::endl;
	return HTMLHead(title, faviconURL);
}

void HTMLDocumentManager::build() {

	HTMLHead head = buildHTMLHead();
	HTMLBody body;

	short choice;
	while (true) {
		HTMLElement* toAdd = nullptr;
		std::cout << "Please enter one of the following: " << std::endl << this->buildMenu << std::endl;

		std::cin >> choice;
		if (choice == 0) {
			//save
			break;
		} else {
			toAdd = createElement(choice);
		}

		if (toAdd != nullptr) {
			body.addElement(toAdd);
			delete toAdd;
		} else {
			std::cout << "Invalid choice!" << std::endl;
		}

	}

	HTMLDocument doc(head, body);
	doc.save();
	std::cout << "Do you want to open the site in browser? (Y/N)" << std::endl;
	char c;
	std::cin >> c;
	if (c == 'Y' || c == 'y') {
		doc.openInBrowser();
	}
}

void HTMLDocumentManager::edit() {
	std::cout << "Please enter the title of your website!" << std::endl;
	std::string title;
	std::cin.ignore();
	std::getline(std::cin, title);

	HTMLDocument doc = HTMLDocument::readFromFile(title);

	short choice;
	while (true) {

		std::cout << "What do you want to do? Please enter one of the following:" << std::endl << this->editMenu << std::endl;
		std::cin >> choice;

		//save
		if (choice == 0) {
			break;
		}
		//search keyword
		else if (choice == 1) {
			std::cout << "Please enter search keyword: \n";
			std::string keyword;
			std::cin.ignore();
			std::getline(std::cin, keyword);
			doc.search(keyword);
		}
		//add element
		else if (choice == 2) {
			HTMLElement* toAdd = nullptr;
			std::cout << "Please enter one of the following: " << std::endl << this->elementChoice << std::endl;
			std::cin >> choice;
			toAdd = createElement(choice);

			if (toAdd != nullptr) {
				doc.addElement(toAdd);
				delete toAdd;
			} else {
				std::cout << "Invalid choice!";
			}

		}
		//edit element
		else if (choice == 3) {
			std::cout << doc.toStringIndexed() << std::endl;
			std::cout << "Enter the index of the element you want to edit!" << std::endl;
			int index;
			std::cin >> index;
			doc.editElement(index);
		}
		//remove element
		else if (choice == 4) {
			std::cout << doc.toStringIndexed() << std::endl;
			std::cout << "Enter the index of the element you want to remove!" << std::endl;
			int index;
			std::cin >> index;
			doc.removeElement(index);
		} else {
			std::cout << "Invalid command!" << std::endl;
		}
	};

	doc.save();
	std::cout << "Do you want to open the site in browser? (Y/N)" << std::endl;
	char c;
	std::cin >> c;
	if (c == 'Y' || c == 'y') {
		doc.openInBrowser();
	}
}
