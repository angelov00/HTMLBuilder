#include "HTMLElement.hpp"

HTMLElement::HTMLElement(const std::string& tag, const std::vector<std::string>& attributes) : tag(tag), attributes(attributes) {};

std::string HTMLElement::getTag() const {
	return this->tag;
}

void HTMLElement::setTag(const std::string& tag) {
	this->tag = tag;
}

std::vector<std::string> HTMLElement::getAttributes() const {
	return this->attributes;
}

void HTMLElement::setAttributes(std::vector<std::string> attributes) {
	this->attributes = attributes;
}