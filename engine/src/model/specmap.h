#ifndef INCLUDED_SPEC_MAP_H
#define INCLUDED_SPEC_MAP_H

#include <map>
#include <string>

#include "utils/autoptr.h"

class IModuleClassSpec;

namespace model
{
	typedef std::map<std::string, utils::AutoPtr<IModuleClassSpec> > SpecMap;
}

#endif
