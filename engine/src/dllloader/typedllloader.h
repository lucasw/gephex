#ifndef INCLUDED_TYPEDLLLOADER_H
#define INCLUDED_TYPEDLLLOADER_H

#include <string>
#include "c_typetables.h"

namespace dllloader
{
  CTypeFunctionTable loadTypeDll(const std::string& filename);
}

#endif
