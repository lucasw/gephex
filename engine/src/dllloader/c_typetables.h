#ifndef INCLUDED_TYPE_TABLES_H
#define INCLUDED_TYPE_TABLES_H


#include "c_functiontypes.h"

/**
 * Tabelle der virtual Member-Funktionen einer DLL-'Klasse'.
 */
class CTypeVTable
{
public:
  newInstanceT newInstance;
  deSerializeT deSerialize;

  deleteInstanceT deleteInstance;

  assignT assign;
  serializeT serialize;

  	attributesEqualT attributesEqual;
	convertTypeT convertType;
};

/**
 * Tabelle aller Funktionen einer DLL-'Klasse' 
 * (virtual member + virtual static).
 */
class CTypeFunctionTable : public CTypeVTable
{
public:
  initT init;
  shutDownT shutDown;
  
  getSpecT getSpec;
  getInfoT getInfo;
};

#endif
