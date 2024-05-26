// Non-Self Closing Elements

#ifndef NSC_ELEMENTS_HPP
#define NSC_ELEMENTS_HPP

#include "NonSelfClosingElement.hpp"

class Paragraph : public NonSelfClosingElement {
public:
	Paragraph(const std::vector<std::string>& attributes, const std::string& content, const std::vector<std::string>& formattingTags) 
		: NonSelfClosingElement("p", attributes, content, formattingTags) {};

	virtual HTMLElement* clone() const override {
		return new Paragraph(*this);
	}
};

class Heading : public NonSelfClosingElement {
public:
	Heading(short size ,const std::vector<std::string>& attributes, const std::string& content, const std::vector<std::string>& formattingTags)
		: NonSelfClosingElement("h" + std::to_string(size), attributes, content, formattingTags) {
	};

	virtual HTMLElement* clone() const override {
		return new Heading(*this);
	}
};

class URL : public NonSelfClosingElement {
public:
	URL(const std::vector<std::string>& attributes, const std::string& content, const std::vector<std::string>& formattingTags)
		: NonSelfClosingElement("a", attributes, content, formattingTags) {
	};

	virtual HTMLElement* clone() const override {
		return new URL(*this);
	}
};

#endif // !NSC_ELEMENTS_HPP
