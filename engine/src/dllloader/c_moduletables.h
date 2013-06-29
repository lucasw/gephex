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
