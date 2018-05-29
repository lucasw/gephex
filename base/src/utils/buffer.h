#ifndef INCLUDED_BUFFER_H
#define INCLUDED_BUFFER_H

//#include <iostream>

namespace utils
{

/**
* Buffer dient zur Speicherung von beliebigen bin�ren Daten.
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
   * Erzeugt einen Buffer der eine Kopie von date der L�nge len enth�lt.
   * @param data Die Daten die der Buffer speichern soll.
   * @param len Die G�sse des Arrays data.
   * @param maxLengthHint is a hint for the maximal length of this buffer.
   *        If set correctly this hint can be used to improve performance,
   *        but at the cost that needed memory is allocated earlier.
   */
  Buffer(const unsigned char* data, int len, int maxLengthHint = 0);


  /**
   * Erzeugt einen Buffer der eine Kopie der Dateb von buf enth�lt.
   * @param buf Der Buffer der kopiert wird.
   */
  Buffer(const Buffer& buf);

  /**
   * Zerst�rt einen Buffer. Alle Aliases f�r getPtr() werden ung�ltig.
   */
  ~Buffer();
  
  /**
   * Kopiert die Daten von buf.
   * Nach dem Aufruf b1 = b2 gilt b1.getLen() == b2.getLen()
   * und b1.getPtr()[i] == b2.getPtr()[i] f�r alle 0 <= i < b1.getLen().
   * Ausserdem werden alle Aliases auf b1_old.getPtr() ung�ltig.
   * @param buf Der Buffer der kopiert wird.
   * @return Referenz auf *this;
   */
  Buffer& operator=(const Buffer& buf);

  /**
   * H�ngt die Daten von buf hinten an.
   * Nach dem Aufruf von b1 += b2 gilt:
   * b1.getLen() == b1_old.getLen() + b2.getLen()
   * und b1.getPtr()[i] == b1_old.getPtr()[i] f�r alle 0 <= i < b1_old.getLen()
   * und b1.getPtr()[i+b1_old.getLen()] == b2.getPtr()[i] 
   * f�r alle 0 <= i < b2.getLen().
   * Ausserdem werden alle Aliases auf b1_old.getPtr() ung�ltig.
   * @param buf Der Buffer der angeh�ngt wird.
   */
  Buffer& operator+=(const Buffer& buf);

  /**
   * Erzeugt einen Buffer der aus den Daten von this und buf besteht.
   * Der Aufruf b1 = b2 + b3 ist �quivalent zu b1 = b2; b1 += b3;.
   * @param buf der Buffer der drangeh�ngt wird.
   * @return Der zusammengesetzte Buffer.
   */
  Buffer operator+(const Buffer& buf) const;
  
  /**
   * Gibt einen Pointer auf die Daten des Buffers zur�ck.
   */
  const unsigned char* getPtr() const;

  /**
   * Gibt die Gr�sse des Buffers in Byte zur�ck.
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
