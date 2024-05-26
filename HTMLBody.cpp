#include "HTMLBody.hpp"

void HTMLBody::addElement(const HTMLElement* element) {
	this->elements.push_back(element->clone());
}

void HTMLBody::editElement(int index) {
	if (index < 0 || index >= elements.size()) {
		std::cout << "Invalid index!\n";
		return;
	}

	this->elements.at(index)->edit();
}

void HTMLBody::removeElement(int index) {
	if (index < 0 || index >= elements.size()) {
		std::cout << "Invalid index!\n";
		return;
	}
	
	delete elements[index];
	elements.erase(elements.begin() + index);
}

std::string HTMLBody::toString() const {
	std::string result = "";
	result.append("<body>\n");
	for (int i = 0; i < this->elements.size(); ++i) {
		result.append(this->elements.at(i)->toString()).append("\n");
	}
	result.append("</body>");
	return result;
}

std::string HTMLBody::toStringIndexed() const {
	std::string result = "";
	result.append("<body>\n");
	for (int i = 0; i < this->elements.size(); ++i) {
		result.append(std::to_string(i) + ": ").append(this->elements.at(i)->toString()).append("\n");
	}
	result.append("</body>");
	return result;
}

void HTMLBody::serialize(std::ostream& os) const {
	size_t elementsCount = this->elements.size();
	os.write((char*)&elementsCount, sizeof(size_t));

	for (int i = 0; i < elementsCount; ++i) {
		this->elements.at(i)->serialize(os);
	}
}


