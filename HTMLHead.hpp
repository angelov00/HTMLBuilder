#ifndef HTML_HEAD_HPP
#define HTML_HEAD_HPP

#include "Serializable.hpp"

class HTMLHead : public Serializable{
private:
	std::string title;
	std::string faviconURL;
public:
	HTMLHead() = default;
	HTMLHead(const std::string& title, const std::string& faviconURL);
	
	std::string getTitle() const;
	void setTitle(const std::string& title);
	std::string getFaviconURL() const;
	void setFaviconURL(const std::string& faviconURL);

	std::string toString() const;
	void serialize(std::ostream& os) const override;
};

#endif // !HTML_HEAD_HPP
