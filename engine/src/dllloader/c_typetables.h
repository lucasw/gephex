/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

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
