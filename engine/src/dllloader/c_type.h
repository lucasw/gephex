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

#ifndef INCLUDED_CTYPE_H
#define INCLUDED_CTYPE_H

#include "interfaces/itype.h"

class CTypeVTable;

/** 
 * This implementation of the IType interface uses a structure with
 * function pointers to create a type object.
 */
class CType : public IType 
{
 public:
  CType(void* instance,const CTypeVTable& ftab, bool isOwner = false);
  virtual ~CType();
  
  virtual void assign(const IType*);
  
  virtual bool serialize (utils::Buffer& b) const;
  virtual void deSerialize (const utils::Buffer& buf);
  
  virtual bool equalAttributes(const TypeAttributes& attr) const;
  
  virtual void convert(const IType& src, const TypeAttributes& attr);

  virtual void* getPointer() const;
  
 private:
  CType(const CType&); // nicht impl.
  const CType& operator=(const CType&); // nicht impl.
  
  const CTypeVTable* const vTab;
  mutable void* instance;
  const bool amOwner;
};

#endif
