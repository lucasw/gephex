#ifndef INCLUDED_IMODULEINFO_BASE_STATION_H
#define INCLUDED_IMODULEINFO_BASE_STATION_H

namespace gui
{
class ModuleInfo;

class IModuleInfoBaseStation
{
public:
	virtual ~IModuleInfoBaseStation() {}
	virtual const ModuleInfo& getModuleInfo(const std::string& moduleClassName) const = 0;
};

}// eon gui
#endif
