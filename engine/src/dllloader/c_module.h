#ifndef INCLUDED_CMODULE_H
#define INCLUDED_CMODULE_H

#include <vector>

#include "interfaces/imodule.h"

#include "utils/autoptr.h"

class CModuleVTable;
class CModuleAttributes;
class UpdateStrategy;
class ITypeFactory;

class CModule : public IModule
{
 public:
  typedef utils::AutoPtr<IType> ITypePtr;

public:
  CModule(void* instance,CModuleVTable&,
	  const CModuleAttributes& attributes,const ITypeFactory&,
	  const std::vector<ITypePtr>& defaultInputTypes);

  virtual ~CModule();

  virtual const std::vector<IInputPtr>& getInputs() const;

  virtual const std::vector<IOutputPtr>& getOutputs() const;

  virtual void dependencies(std::list<IInput*>&);

  virtual void update();

  virtual bool isDeterministic() const;

  virtual void parseInput(const char*,int);

  void setData(const IInput*/*,const IType**/);

private:

  void* m_instance;
  CModuleVTable* m_vtable;

  std::vector<IInputPtr> inputs;
  std::vector<IOutputPtr> outputs;

  bool _isDeterministic;
  typedef utils::AutoPtr<UpdateStrategy> UpdateStrategyPtr;
  UpdateStrategyPtr us;

  //CModule(const CModule&);

  const CModule& operator=(const CModule&); // nicht impl.

  void doUpdate();

};


#endif

