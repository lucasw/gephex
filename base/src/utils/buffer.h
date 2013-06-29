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

#ifndef INCLUDED_BUFFER_H
#define INCLUDED_BUFFER_H

//#include <iostream>

namespace utils
{

/**
* Buffer dient zur Speicherung von beliebigen binären Daten.
*/

class Buffer
{
public:

  /**
   * Erzeugt einen leeren Buffer. D.h. getLen() == 0 und
   * getPtr() == 0.
   * @param maxLengthHint is a hint for the maximal length of this buffer.
   *        If set correctly this hint can be used to improve performance,
   *        but at the cost that needed memory is allocated earlier.
   */
  explicit Buffer(int maxLengthHint = 0);

  /**
   * Erzeugt einen Buffer der eine Kopie von date der Länge len enthält.
   * @param data Die Daten die der Buffer speichern soll.
   * @param len Die Gösse des Arrays data.   
   * @param maxLengthHint is a hint for the maximal length of this buffer.
   *        If set correctly this hint can be used to improve performance,
   *        but at the cost that needed memory is allocated earlier.
   */
  Buffer(const unsigned char* data, int len, int maxLengthHint = 0);

  /**
   * Erzeugt einen Buffer der eine Kopie von date der Länge len enthält.
   * @param data Die Daten die der Buffer speichern soll.
   * @param len Die Gösse des Arrays data.
   * @param owner Wenn owner == true dann ist der Buffer neuer owner von 
   *              data
   * @param maxLengthHint is a hint for the maximal length of this buffer.
   *        If set correctly this hint can be used to improve performance,
   *        but at the cost that needed memory is allocated earlier.
   */
  Buffer(unsigned char* data, int len, bool owner = false,
	     int maxLengthHint = 0);


  /**
   * Erzeugt einen Buffer der eine Kopie der Dateb von buf enthält.
   * @param buf Der Buffer der kopiert wird.
   */
  Buffer(const Buffer& buf);

   /**
   * Erzeugt einen Buffer der eine Kopie der Dateb von buf enthält.
   * @param buf Der Buffer der kopiert wird.
   * @param maxLengthHint is a hint for the maximal length of this buffer.
   *        If set correctly this hint can be used to improve performance,
   *        but at the cost that needed memory is allocated earlier.
   */
  Buffer(const Buffer& buf, int maxLengthHint);

  /**
   * Zerstört einen Buffer. Alle Aliases für getPtr() werden ungültig.
   */
  ~Buffer();
  
  /**
   * Kopiert die Daten von buf.
   * Nach dem Aufruf b1 = b2 gilt b1.getLen() == b2.getLen()
   * und b1.getPtr()[i] == b2.getPtr()[i] für alle 0 <= i < b1.getLen().
   * Ausserdem werden alle Aliases auf b1_old.getPtr() ungültig.
   * @param buf Der Buffer der kopiert wird.
   * @return Referenz auf *this;
   */
  Buffer& operator=(const Buffer& buf);

  /**
   * Hängt die Daten von buf hinten an.
   * Nach dem Aufruf von b1 += b2 gilt:
   * b1.getLen() == b1_old.getLen() + b2.getLen()
   * und b1.getPtr()[i] == b1_old.getPtr()[i] für alle 0 <= i < b1_old.getLen()
   * und b1.getPtr()[i+b1_old.getLen()] == b2.getPtr()[i] 
   * für alle 0 <= i < b2.getLen().
   * Ausserdem werden alle Aliases auf b1_old.getPtr() ungültig.
   * @param buf Der Buffer der angehängt wird.
   */
  Buffer& operator+=(const Buffer& buf);

  /**
   * Erzeugt einen Buffer der aus den Daten von this und buf besteht.
   * Der Aufruf b1 = b2 + b3 ist äquivalent zu b1 = b2; b1 += b3;.
   * @param buf der Buffer der drangehängt wird.
   * @return Der zusammengesetzte Buffer.
   */
  Buffer operator+(const Buffer& buf) const;
  
  /**
   * Gibt einen Pointer auf die Daten des Buffers zurück.
   */
  const unsigned char* getPtr() const;

  /**
   * Gibt die Grösse des Buffers in Byte zurück.
   */
  int getLen() const;

  //void setData(const char* data, int len);

//	friend std::ostream& operator<< (std::ostream&, const Buffer&);
	
 private:
  unsigned char* m_buffer;
  int m_len;
  int m_capacity;
};

//std::ostream& operator<< (std::ostream&, const Buffer&);
//std::istream& operator>> (std::istream&, Buffer&);

}

#endif
