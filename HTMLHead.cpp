#include "HTMLHead.hpp"

HTMLHead::HTMLHead(const std::string& title, const std::string& faviconURL) : title(title), faviconURL(faviconURL) {};

std::string HTMLHead::getTitle() const {
	return this->title;
}

void HTMLHead::setTitle(const std::string& title) {
	this->title = title;
}

std::string HTMLHead::getFaviconURL() const {
	return this->faviconURL;
}

void HTMLHead::setFaviconURL(const std::string& faviconURL) {
	this->faviconURL = faviconURL;
}

std::string HTMLHead::toString() const {
	std::string result;
	result.append("\t<head>\n");
	result.append("\t\t<title>").append(this->title).append("</title>\n");
	result.append("\t\t<link rel=\"icon\" type=\"image/x-icon\" href=\"").append(this->faviconURL).append("\">\n");
	result.append("\t</head>\n");
	return result;
}

void HTMLHead::serialize(std::ostream& os) const {
	size_t sizeOfTitle = this->title.size();
	os.write((char*)&sizeOfTitle, sizeof(size_t));
	os.write((char*)this->title.c_str(), sizeOfTitle);

	size_t sizeOfFaviconURL = this->faviconURL.size();
	os.write((char*)&sizeOfFaviconURL, sizeof(size_t));
	os.write((char*)this->faviconURL.c_str(), sizeOfFaviconURL);
}