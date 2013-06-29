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

#ifndef INCLUDED_NAMERESOLVER_H
#define INCLUDED_NAMERESOLVER_H

#include <map>
#include <string>

/**
 * Diese Klasse hat die Aufgabe eine eindeutige Zuordnung zwischen 
 * Objekten(Moduleklassen und Typen) und deren Identifiern(int) herzustellen. 
 */
class NameResolver
{
 public:
  NameResolver();

  /**
   * Registriert eine neues Objekt anhand seines Namens.
   * @param name eindeutiger Objektname
   * @return Falls der Name noch nicht registriert ist wird eine 
   *         eindeutige ID zurueckgegeben
   * @exception Wirft runtime_error falls Name bereits registriert ist.
   */
  int registerObject(const std::string& name);

  /**
   * Liefert die ID eines Objekts anhand des Names zurück.
   * @param name Objektname
   * @return Falls der Name registriert ist wird die zugehoerige ID
   *         zurueckgegeben sonst wird er registriert und eine
   *         neue ID zurückgegeben.
   */
  int getObjectID(const std::string& name) ;

 private:
  typedef std::map<std::string,int> StringMap;
  StringMap hash;
  int lastID;
};

#endif
