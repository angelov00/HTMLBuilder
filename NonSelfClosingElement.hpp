#ifndef NON_SELF_CLOSING_ELEMENT_HPP
#define NON_SELF_CLOSING_ELEMENT_HPP

#include "HTMLElement.hpp"

class NonSelfClosingElement : public HTMLElement {
protected:
	std::string content;
	std::vector<std::string> formattingTags;
public:
	NonSelfClosingElement() = default;
	NonSelfClosingElement(const std::string& tag, const std::vector<std::string>& attributes,
		const std::string& content, const std::vector<std::string> formattingTags);
	virtual ~NonSelfClosingElement() = default;

	virtual HTMLElement* clone() const = 0;
	virtual std::string toString() const override;
	virtual void serialize(std::ostream& os) const override;

	virtual void edit() override;
};


#endif // !NON_SELF_CLOSING_ELEMENT_HPP
