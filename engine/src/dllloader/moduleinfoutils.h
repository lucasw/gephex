#ifndef INCLUDED_MODULE_INFO_UTILS_H
#define INCLUDED_MODULE_INFO_UTILS_H

#include <vector>
#include <string>

class ModuleAttributes;

namespace utils {
class Buffer;
}


namespace dllloader
{

/**
 * Verschafft Zugang zu Zusatzinformationen ueber Dlls. Das sind
 * die Informationen die von der engine nicht benoetigt werden.
 * Der von getInfo() zurückgelieferte Buffer wird geparst
 * und mit zusaetzlichen Informationen (eindeutiger Name, Typen der 
 * Plugs) erweitert.
 */
struct ModuleInfo
{
 static utils::Buffer enrichInfo(const char* data,int len,
				 const std::string& name,
				 const std::vector<std::string>& inNames,
				 const std::vector<std::string>& outNames);

};

}
#endif
