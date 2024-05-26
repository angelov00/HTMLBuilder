#ifndef HTML_ELEMENT_HPP
#define HTML_ELEMENT_HPP

#include "Serializable.hpp"
#include <string>
#include <vector>
#include <iostream>

class HTMLElement : public Serializable{
protected:
	std::string tag;
	std::vector<std::string> attributes;
public:
	HTMLElement() = default;
	HTMLElement(const std::string& tag, const std::vector<std::string>& attributes);
	virtual ~HTMLElement() = default;

	virtual HTMLElement* clone() const = 0;
	
	virtual std::string toString() const = 0;
	virtual void serialize(std::ostream& os) const override = 0;
	virtual void edit() = 0;

	//getters and setters
	std::string getTag() const;
	void setTag(const std::string& tag);
	std::vector<std::string> getAttributes() const;
	void setAttributes(std::vector<std::string> attributes);
};

#endif // !HTML_ELEMENT_HPP
