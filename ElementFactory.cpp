#include "ElementFactory.hpp"

std::vector<std::string> ElementFactory::styleTextElement() {
    std::vector<std::string> vec;
    std::string choices;
    std::cout << "Do you want to change the text style?\n"
        << "Please enter one of the following commands: (You can select multiple, just separate them by a comma.)\n"
        << "\t1. Regular Text\n"
        << "\t2. Bold\n"
        << "\t3. Italic\n"
        << "\t4. Underlined\n";

    std::cin.ignore();
    std::getline(std::cin, choices);

    for (char c : choices) {
        switch (c) {
        case '2':
            vec.push_back("b");
            break;
        case '3':
            vec.push_back("em");
            break;
        case '4':
            vec.push_back("u");
            break;
        default:
            break;
        }
    }
    return vec;
}

std::vector<std::string> ElementFactory::formatElement(ElementType type) {
    switch (type) {
    case HEADING:
    case PARAGRAPH:
    case HYPERLINK:
        return styleTextElement();
    default:
        return {};
    }
}

HTMLElement* ElementFactory::createElement(ElementType type) {
    switch (type) {
    case HEADING: {
        std::vector<std::string> attributes;

        std::cout << "Please enter the size of the heading (1-6):\n";
        short size;
        std::cin >> size;
        std::cin.ignore();

        std::cout << "Please enter the content of the heading:\n";
        std::string content;
        std::getline(std::cin, content);

        std::vector<std::string> formattingTags = formatElement(type);

        return new Heading(size, attributes, content, formattingTags);
    }
    case PARAGRAPH: {
        std::vector<std::string> attributes;

        std::cout << "Please enter the content of the paragraph:\n";
        std::cin.ignore();
        std::string content;
        std::getline(std::cin, content);

        std::vector<std::string> formattingTags = formatElement(type);

        return new Paragraph(attributes, content, formattingTags);
    }
    case HYPERLINK: {
        std::vector<std::string> attributes;

        std::cout << "Please enter the URL:\n";
        std::cin.ignore();
        std::string urlString;
        std::getline(std::cin, urlString);

        attributes.push_back("href=\"" + urlString + "\"");

        std::cout << "Please enter the content of the URL:\n";
        std::string content;
        std::getline(std::cin, content);

        std::vector<std::string> formattingTags = formatElement(type);

        return new URL(attributes, content, formattingTags);
    }
    case IMAGE: {
        std::vector<std::string> attributes;

        std::cout << "Please enter the source link of the image:\n";
        std::cin.ignore();
        std::string imageURL;
        std::getline(std::cin, imageURL);

        std::cout << "Please enter the alt text of the image:\n";
        std::cin.ignore();
        std::string alttext;
        std::getline(std::cin, alttext);

        std::cout << "Please enter the width and the height of the image:\n";
        unsigned short width, height;
        std::cin >> width >> height;

        attributes.push_back("src=\"" + imageURL + "\"");
        attributes.push_back("alt=\"" + alttext + "\"");
        attributes.push_back("width=\"" + std::to_string(width) + "\"");
        attributes.push_back("height=\"" + std::to_string(height) + "\"");

        return new Image(attributes);
    }
    case HORIZONTAL_LINE: {
        return new HorizontalLine();
    }
    case NEW_LINE: {
        return new NewLine();
    }
    default:
        return nullptr;
    }
}