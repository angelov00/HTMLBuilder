#ifndef HTML_BODY_HPP
#define HTML_BODY_HPP

#include "HTMLElement.hpp"
#include "Serializable.hpp"
#include "iostream"

class HTMLBody {
private:
	std::vector<HTMLElement*> elements;
public:
	HTMLBody() = default;
	void addElement(const HTMLElement* element);
	void editElement(int index);
	void removeElement(int index);
	std::string toString() const;
	std::string toStringIndexed() const;

	virtual void serialize(std::ostream& os) const;
};


#endif // !HTML_BODY_HPP
