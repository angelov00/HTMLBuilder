#include "NonSelfClosingElement.hpp"

void NonSelfClosingElement::edit() {
	std::cout << "Enter the new content of the element!\n";
	std::cin.ignore();
	std::string newContent;
	std::getline(std::cin, newContent);
	this->content = newContent;
}

NonSelfClosingElement::NonSelfClosingElement(const std::string& tag, const std::vector<std::string>& attributes,
	const std::string& content, const std::vector<std::string> formattingTags) : HTMLElement(tag, attributes), content(content), formattingTags(formattingTags) {
}

std::string NonSelfClosingElement::toString() const {
	std::string result = "";
	result.append("<").append(this->tag);

	if (!this->attributes.empty()) {
		result.append(" ");
		for (int i = 0; i < this->attributes.size(); ++i) {
			result.append(" ");
			result.append(this->attributes.at(i));
		}
	}
	result.append(">");

	if (!this->formattingTags.empty()) {
		for (int i = 0; i < this->formattingTags.size(); ++i) {
			result.append("<").append(this->formattingTags.at(i)).append(">");
		}
	}

	result.append(this->content);

	if (!this->formattingTags.empty()) {
		for (int i = this->formattingTags.size() - 1; i >= 0; --i) {
			result.append("</").append(this->formattingTags.at(i)).append(">");
		}
	}

	result.append("</").append(this->tag).append(">");
	return result;
}

void NonSelfClosingElement::serialize(std::ostream& os) const {
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

	//content
	size_t sizeOfContent = this->content.size();
	os.write((char*)&sizeOfContent, sizeof(size_t));
	os.write((char*)this->content.c_str(), sizeOfContent);

	//formattingTags
	size_t formattingTagsCount = this->formattingTags.size();
	os.write((char*)&formattingTagsCount, sizeof(size_t));
	for (int i = 0; i < formattingTagsCount; ++i) {
		size_t sizeOfCurrentFormattingTag = this->formattingTags.at(i).size();
		os.write((char*)&sizeOfCurrentFormattingTag, sizeof(size_t));
		os.write((char*)this->formattingTags.at(i).c_str(), sizeOfCurrentFormattingTag);
	}
}
