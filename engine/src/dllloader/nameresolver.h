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
