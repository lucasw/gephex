#ifndef INCLUDED_MODULE_INFO_H
#define INCLUDED_MODULE_INFO_H

#include <string>
#include <vector>

#include "pluginfo.h"
#include "utils/autoptr.h"

namespace gui
{

class Xpm;

class ModuleInfo
{
public:
	ModuleInfo(const ModuleInfo& mi);

	ModuleInfo(const std::string& _identifer,const std::string& _name,
		const std::string& group, const std::vector<PlugInfo>& _inputs,
		const std::vector<PlugInfo>& _outputs, 
		utils::AutoPtr<Xpm>& _pixmap);
	
	ModuleInfo& operator=(const ModuleInfo& mi);
	
	~ModuleInfo();
	
	std::string getName() const;
	std::string getIdentifier() const;
	std::string getGroup() const;

	const std::vector<PlugInfo>& getInputs() const;
	const std::vector<PlugInfo>& getOutputs() const;
	const Xpm& getIcon() const;
	

private:
	std::string identifier;
	std::string name;
	std::string group;
	std::vector<PlugInfo> inputs;
	std::vector<PlugInfo> outputs;
	utils::AutoPtr<Xpm> pixmap;
};

} // end of namespace gui
#endif
