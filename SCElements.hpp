//Self-Closing Elements

#ifndef SC_ELEMENTS_HPP
#define SC_ELEMENTS_HPP

#include "SelfClosingElement.hpp"

class Image : public SelfClosingElement{
public:
	Image(const std::vector<std::string>& attributes) : SelfClosingElement("img", attributes) {};

	virtual HTMLElement* clone() const override {
		return new Image(*this);
	}

	virtual void edit() override {
		std::cout << "What do you want to change about the image?\n";
		std::cout << "\t1.Photo Url\n" << "\t2.Alttext\n" << "\t3..Width\n" << "\t4.Height\n";
		short choice;
		std::cin >> choice;
		std::cin.ignore();

		if (choice == 1) {
			std::cout << "Enter the new URL of the picture!\n";
			std::cin.ignore();
			std::string newURL;
			std::getline(std::cin, newURL);
			this->attributes.at(0) = "src=\"" + newURL + "\"";
		}
		else if (choice == 2) {
			std::cout << "Enter the new alternative text of the picture!\n";
			std::cin.ignore();
			std::string newText;
			std::getline(std::cin, newText);
			this->attributes.at(1) = "alt=\"" + newText + "\"";
		} else if (choice == 3) {
			std::cout << "Enter the new width of the picture!\n";
			unsigned width;
			std::cin >> width;
			this->attributes.at(2) = "width=\"" + std::to_string(width) + "\"";
		} else if (choice == 4) {
			std::cout << "Enter the new height of the picture!\n";
			unsigned height;
			std::cin >> height;
			this->attributes.at(3) = "height=\"" + std::to_string(height) + "\"";
		} else {
			std::cout << "Invalid choice!\n";
		}

	}
};

class HorizontalLine : public SelfClosingElement {
public:
	HorizontalLine() : SelfClosingElement("hr", {}) {};

	virtual HTMLElement* clone() const override {
		return new HorizontalLine(*this);
	}

	virtual void edit() override {
		std::cout << "This element cannot be edited!" << std::endl;
	}
};

class NewLine : public SelfClosingElement {
public:
	NewLine() : SelfClosingElement("br", {}) {};

	virtual HTMLElement* clone() const override {
		return new NewLine(*this);
	}

	virtual void edit() override {
		std::cout << "This element cannot be edited!" << std::endl;
	}
};
#endif // !SC_ELEMENTS_HPP
