#ifndef INCLUDED_IMODULE_CLASS_H
#define INCLUDED_IMODULE_CLASS_H

class IModule;
class ITypeFactory;

class IModuleClass
{
public:
  virtual ~IModuleClass() {}
  virtual IModuleClass* clone() const = 0;
  virtual IModule* buildInstance(const ITypeFactory& tFactory) const = 0;


};

#endif
