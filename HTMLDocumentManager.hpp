#ifndef HTML_DOCUMENT_MANAGER
#define HTML_DOCUMENT_MANAGER

#include "ElementFactory.hpp"
#include "ElementType.hpp"
#include "HTMLDocument.hpp"

class HTMLDocumentManager {
private:

	const std::string elementChoice = "\n\t1.Heading\n\t2.Text paragraph\n\t3.Picture\n\t4.URL\n\t5.New Line\n\t6.Horizontal Line";
	const std::string editMenu = "\t0.Save\n\t1.Search\n\t2.Add\n\t3.Edit\n\t4.Remove";
	const std::string buildMenu = "\t0.Save" + elementChoice;
	
	HTMLHead buildHTMLHead();
	HTMLElement* createElement(short choice);
public:
	void build();
	void edit();
};

#endif // !HTML_DOCUMENT_MANAGER
