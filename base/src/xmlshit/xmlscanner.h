#ifndef __INCLUDED_XMLSCANNER_H__
#define __INCLUDED_XMLSCANNER_H__

#include <string>

class XMLTokenListener;

class XMLFileScanner
{	
private:
	XMLTokenListener& l;
	int pos;

	void scanInfoSection(std::string& text);
	void scanNodeSection(std::string& text);
	void scanCtrlSection(std::string& text);
	void scanConnectionSection(std::string& text);
public:
	XMLFileScanner(XMLTokenListener&);
	
	void scan(std::string& text);
};	

#endif
