#ifndef HTML_DOCUMENT_HPP
#define HTML_DOCUMENT_HPP

#include <regex>

#include "HTMLHead.hpp"
#include "HTMLBody.hpp"
#include "NSCElements.hpp"
#include "SCElements.hpp"

class HTMLDocument : public Serializable{
private:
	HTMLHead head;
	HTMLBody body;

	//helper functions
	static std::string deserializeTag(std::istream& is);
	static std::vector<std::string> deserializeAttributes(std::istream& is);
	static std::string deserializeContent(std::istream& is);
	static std::vector<std::string> deserializeFormattingTags(std::istream& is);
public:
	HTMLDocument() = default;
	HTMLDocument(const HTMLHead& head, const HTMLBody& body);

	void save();
	void openInBrowser();
	std::string getTitle() const;
	
	std::string toString() const;
	std::string toStringIndexed() const;

	void search(const std::string& keyword);
	void addElement(const HTMLElement* element);
	void removeElement(int index);
	void editElement(int index);

	void serialize(std::ostream& os) const override;

	static HTMLDocument readFromFile(const std::string& title);
};

#endif // !HTML_DOCUMENT_HPP
