#ifndef INCLUDED_MODULE_TABLES_H
#define INCLUDED_MODULE_TABLES_H

#include <vector>

#include "c_functiontypes.h"

class TypeAttributes;

class COutputVTable
{
public:
	setOutputT setOutput;
};

class CInputVTable
{
public:
	 setInputT setInput;
};

/**
 * Tabelle der virtual Member-Funktionen einer DLL-'Klasse'.
 */
class CModuleVTable : public COutputVTable, public CInputVTable
{
public:
	newInstanceT newInstance;
	deleteInstanceT deleteInstance;
			
	updateT update;
	
	parseInputT parseInput;
	
	strongDependenciesCalculatedT strongDependenciesCalculated;
	getPatchLayoutT getPatchLayout;
};

/**
 * Tabelle aller Funktionen einer DLL-'Klasse' 
 * (virtual member + virtual static).
 */
class CModuleFunctionTable : public CModuleVTable
{
public:
  initT init;
  shutDownT shutDown;
    
  getInfoT getInfo;

  getSpecT getSpec;
  getInputSpecT getInputSpec;
  getOutputSpecT getOutputSpec;
  getInputAttributesT getInputAttributes;
};

/**
* Statische Attribute einer DLL-'Klasse'.
*/
class CModuleAttributes
{
public:
  std::vector<int> inputs;
  std::vector<int> outputs;
  std::vector<bool> isConstInput;
  std::vector<bool> isStrongDependency;
  std::vector<const TypeAttributes*> fixedAttributes;
  bool isDeterministic;
};

#endif
