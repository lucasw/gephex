#ifndef INCLUDED_TYPE_TABLES_H
#define INCLUDED_TYPE_TABLES_H

#include "c_functiontypes.h"
#include "utils/autoptr.h"
#include "utils/sharedlibrary.h"

/**
 * Tabelle der virtual Member-Funktionen einer DLL-'Klasse'.
 */
class CTypeVTable
{
public:
  CTypeVTable(utils::AutoPtr<utils::SharedLibrary> sl_)
    :sl(sl_){};
  newInstanceT newInstance;
  deSerializeT deSerialize;

  deleteInstanceT deleteInstance;

  assignT assign;
  serializeT serialize;

  attributesEqualT attributesEqual;
  convertTypeT convertType;
 private:
  utils::AutoPtr<utils::SharedLibrary> sl;
};

/**
 * Tabelle aller Funktionen einer DLL-'Klasse' 
 * (virtual member + virtual static).
 */
class CTypeFunctionTable : public CTypeVTable
{
 public:
  CTypeFunctionTable(utils::AutoPtr<utils::SharedLibrary> sl_)
    :CTypeVTable(sl_){};
  initT init;
  shutDownT shutDown;
  
  getSpecT getSpec;
  getInfoT getInfo;
};

#endif
