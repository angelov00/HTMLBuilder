#ifndef SELF_CLOSING_ELEMENT_HPP
#define SELF_CLOSING_ELEMENT_HPP

#include "HTMLElement.hpp"

class SelfClosingElement : public HTMLElement{
protected:
public:
	SelfClosingElement() = default;
	SelfClosingElement(const std::string& tag, const std::vector<std::string>& attributes);
	virtual ~SelfClosingElement() = default;

	virtual HTMLElement* clone() const = 0;
	virtual std::string toString() const override;
	virtual void serialize(std::ostream& os) const override;
};

#endif // !SELF_CLOSING_ELEMENT_HPP
