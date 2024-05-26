#include "SelfClosingElement.hpp"

SelfClosingElement::SelfClosingElement(const std::string& tag, const std::vector<std::string>& attributes) : HTMLElement(tag, attributes) {};

std::string SelfClosingElement::toString() const {
	std::string result = "";

	result.append("<").append(this->tag);
	if (!this->attributes.empty()) {
		result.append(" ");
		for (int i = 0; i < this->attributes.size(); ++i) {
			result.append(" ");
			result.append(this->attributes.at(i));
		}
	}

	result.append("/>");
	return result;
}

void SelfClosingElement::serialize(std::ostream& os) const {
	//tag
	size_t sizeOfTag = this->tag.size();
	os.write((char*)&sizeOfTag, sizeof(size_t));
	os.write((char*)this->tag.c_str(), sizeOfTag);

	//attributes
	size_t attributesCount = this->attributes.size();
	os.write((char*)&attributesCount, sizeof(size_t));
	for (int i = 0; i < attributesCount; ++i) {
		size_t sizeOfCurrentAttribute = this->attributes.at(i).size();
		os.write((char*)&sizeOfCurrentAttribute, sizeof(size_t));
		os.write((char*)this->attributes.at(i).c_str(), sizeOfCurrentAttribute);
	}
}