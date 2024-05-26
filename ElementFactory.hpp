#ifndef ELEMENT_FACTORY_HPP
#define ELEMENT_FACTORY_HPP

#include "NSCElements.hpp"
#include "SCElements.hpp"
#include "ElementType.hpp"
#include <iostream>


class ElementFactory {
private:
    static std::vector<std::string> styleTextElement();
public:
    static std::vector<std::string> formatElement(ElementType type);
    static HTMLElement* createElement(ElementType type);
};


#endif // !ELEMENT_FACTORY_HPP
