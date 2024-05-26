#include "HTMLDocument.hpp"

HTMLDocument::HTMLDocument(const HTMLHead& head, const HTMLBody& body) : head(head), body(body) {};

void HTMLDocument::editElement(int index) {
	this->body.editElement(index);
}

//save the data both in html and binary format
void HTMLDocument::save() {

	std::string htmlFilePath = this->getTitle() + ".html";
	std::string binaryFilePath = this->getTitle() + ".data";

	std::ofstream htmlFile;
	std::ofstream binaryFile;

	htmlFile.open(htmlFilePath, std::ios::out);
	binaryFile.open(binaryFilePath, std::ios::binary | std::ios::out);

	//html format
	htmlFile << this->toString();
	//binary
	this->serialize(binaryFile);

	htmlFile.close();
	binaryFile.close();
}

//open the html file in the system default browserSSS
void HTMLDocument::openInBrowser(){
	std::string filePath = this->getTitle() + ".html";
	
	// Поради някаква причина прави проблем, ако има интервал в името на файла
	#ifdef _WIN32
		std::string command = "start " + filePath;
	#elif __APPLE__
		std::string command = "open " + filePath;
	#elif __linux__
		std::string command = "xdg-open " + filePath;
	#else
	#error "Unsupported operating system"
	#endif

	system(command.c_str());
}

void HTMLDocument::serialize(std::ostream& os) const {
	this->head.serialize(os);
	this->body.serialize(os);
}

std::string HTMLDocument::toString() const {
	std::string result = "";
	result.append("<html>\n");
	result.append(head.toString());
	result.append(body.toString());
	result.append("\n</html>");
	return result;
}

std::string HTMLDocument::toStringIndexed() const {
	std::string result = "";
	result.append("<html>\n");
	result.append(head.toString());
	result.append(body.toStringIndexed());
	result.append("\n</html>");
	return result;
}

void HTMLDocument::search(const std::string& keyword) {

	/*
	Използваме регекс библиотеката и получаваме итератор за съвпаденията. Итерирате и последвователно 
	заместваме съвпаденията с цветно форматиране, като пазим съответно позицията на заместения текст
	https://www.geeksforgeeks.org/program-to-find-all-match-of-a-regex-in-a-string/
	*/
	std::string text = this->toString();
	std::string colorStart = "\033[1;31m";  // Red color
	std::string colorEnd = "\033[0m";       // Reset color

	std::regex keywordRegex(keyword);
	std::string modifiedText;
	std::sregex_iterator currentMatch(text.begin(), text.end(), keywordRegex);
	std::sregex_iterator lastMatch;

	size_t lastPos = 0;

	while (currentMatch != lastMatch) {
		std::smatch match = *currentMatch;
		modifiedText += text.substr(lastPos, match.position() - lastPos);
		modifiedText += colorStart + match.str() + colorEnd;
		lastPos = match.position() + match.length();
		++currentMatch;
	}
	modifiedText += text.substr(lastPos);

	std::cout << modifiedText << std::endl;
}

std::string HTMLDocument::getTitle() const {
	return this->head.getTitle();
}

void HTMLDocument::addElement(const HTMLElement* element) {
	this->body.addElement(element);
}

void HTMLDocument::removeElement(int index) {
	this->body.removeElement(index);
}

HTMLDocument HTMLDocument::readFromFile(const std::string& pageTitle) {
	std::ifstream input;
	std::string filePath = pageTitle + ".data";

	input.open(filePath, std::ios::binary | std::ios::in);

	if (!input.is_open()) {
		throw "Invalid file name";
	}

	//Deserialize Head
	size_t sizeOfTitle;
	input.read((char*)&sizeOfTitle, sizeof(size_t));
	std::string title(sizeOfTitle, '\0');
	input.read(&title[0], sizeOfTitle);

	size_t sizeOfFaviconURL;
	input.read((char*)&sizeOfFaviconURL, sizeof(size_t));
	std::string faviconURL(sizeOfFaviconURL, '\0');
	input.read(&faviconURL[0], sizeOfFaviconURL);

	HTMLHead head(title, faviconURL);

	//Deserialize Body
	HTMLBody body;

	size_t elementsCount = 0;
	input.read((char*)&elementsCount, sizeof(size_t));

	for (int i = 0; i < elementsCount; ++i) {

		HTMLElement* toAdd = nullptr;

		//deserialize tag
		std::string tag = HTMLDocument::deserializeTag(input);

		//deserialize attributes
		std::vector<std::string> attributes = HTMLDocument::deserializeAttributes(input);

		if (tag.compare("p") == 0) {
			std::string content = HTMLDocument::deserializeContent(input);
			std::vector<std::string> formattingTags = HTMLDocument::deserializeFormattingTags(input);
			toAdd = new Paragraph(attributes, content, formattingTags);
		}
		else if (tag.compare("hr") == 0) {
			toAdd = new HorizontalLine();
		}
		else if (tag.at(0) == 'h') {
			std::string content = HTMLDocument::deserializeContent(input);
			std::vector<std::string> formattingTags = HTMLDocument::deserializeFormattingTags(input);
			int size = tag.at(1) - '0';
			toAdd = new Heading(size, attributes, content, formattingTags);
		}
		else if (tag.compare("img") == 0) {
			toAdd = new Image(attributes);
		}
		else if (tag.compare("a") == 0) {
			std::string content = HTMLDocument::deserializeContent(input);
			std::vector<std::string> formattingTags = HTMLDocument::deserializeFormattingTags(input);
			toAdd = new URL(attributes, content, formattingTags);
		}
		else if (tag.compare("br") == 0) {
			toAdd = new NewLine();
		}

		if (toAdd != nullptr) {
			body.addElement(toAdd);
			delete toAdd;
		}
	}

	return HTMLDocument(head, body);
}

std::string HTMLDocument::deserializeContent(std::istream& is) {
	size_t size;
	is.read((char*)&size, sizeof(size_t)); // Read the size of the content

	std::string content(size, '\0'); // Prepare a string of the appropriate size
	is.read(&content[0], size); // Read the actual content

	return content;
}

std::vector<std::string> HTMLDocument::deserializeFormattingTags(std::istream& is) {
	size_t count;
	is.read((char*)&count, sizeof(size_t));

	std::vector<std::string> tags(count);
	for (size_t i = 0; i < count; ++i) {
		size_t tagSize;
		is.read((char*)&tagSize, sizeof(size_t));

		tags[i].resize(tagSize);
		is.read(&tags[i][0], tagSize);
	}

	return tags;
}

std::string HTMLDocument::deserializeTag(std::istream& is) {
	size_t size;
	is.read((char*)&size, sizeof(size_t));

	std::string result(size, '\0');
	is.read(&result[0], size);

	return result;
}

std::vector<std::string> HTMLDocument::deserializeAttributes(std::istream& is) {
	std::vector<std::string> result;
	size_t attributesCount;
	is.read((char*)&attributesCount, sizeof(size_t));

	for (size_t i = 0; i < attributesCount; ++i) {
		size_t sizeOfCurrentAttribute;
		is.read((char*)&sizeOfCurrentAttribute, sizeof(size_t));

		std::string attribute(sizeOfCurrentAttribute, '\0');
		is.read(&attribute[0], sizeOfCurrentAttribute);

		result.push_back(attribute);
	}

	return result;
}