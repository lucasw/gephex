#ifndef INCLUDED_STRUCT_READER_H
#define INCLUDED_STRUCT_READER_H

#include <string>
#include <stdexcept>
#include <map>

namespace utils
{

/**
 * Mit dieser Klasse kann man strings auslesen die in einem
 * pseudo c-struct format geschrieben sind. Diese strings sehen so aus:
 * "struct_name { var1=value1; var2=value2; ... }".
 * Zulaessige values sind:
 *  - text ohne whitespaces (richtig: "dr_schiwago", falsch:"dr schiwago")
 *  - text in eckigen klammern mit whitespaces ("[dr schiwago]").
 *    die eckigen klammern werden ignoriert (-> "dr schiwago")
 *  - true|false
 *  - ganze zahlen im wertebereich einer int.
 * 
 * Diese Klasse garantiert keine Typsicherheit. Hat man z.B. in einer
 * c-struct eine Variable "v1=true" so ist es moeglich v1 mit der
 * Funktion StructReader::getStringValue("v1") auszulesen. Als Ergebnis
 * erhaelt man den String "true". Es ist aber auch moeglich die
 * Variable mit StructReader::getBoolValue("v1") auszulesen. Dann
 * erhaelt man als Ergebnis den boolschen Wert true.
 * Genauso kann man Zahlen auch als Strings auslesen.
 * Man kann jedoch nicht Zahlen als Bools bzw. Bools als Zahlen lesen.
 */
class StructReader
{
 public:
  typedef std::map<std::string,std::string> ConfigMap;

  /**
   * Konstruiert einen StructReader der die pseudo c-struct in text
   * einliest.
   * @param text Die pseudo c-struct als string.
   * @exception std::runtime_error falls text syntaxfehler enthaelt.
   */
  StructReader(const std::string& text);

  /**
   * Konstruiert einen StructReader mit schon eingelesenen (Name,Wert)
   * Paaren.
   * @param map Enhält Paare aus Namen und Werten die dann über diesen
   *            StructReader ausgelesen werden können.
   */
  StructReader(const std::map<std::string,std::string>& map);

  ~StructReader();
  /**
   * Gibt den Namen der gelesenen struct zurueck.
   * @return Name der struct (der string der vor der oeffnenden
   *         geschweiften Klammer steht).
   */
  std::string getName() const;

  /**
   * Gibt den Wert der Variablen mit Namen name als bool zurueck.
   * @param name Name der Variablen
   * @return true falls name="true" in der struct vorkommt,
   *         false falls name="false" vorkommt.
   * @throw std::runtime_error Falls weder name="true" noch name="false"
   *         vorkommt. Dann existiert entweder die Variable gar nicht in
   *         der c-struct oder sie hat einen anderen Typ (int oder string).
   */
  bool getBoolValue(const std::string& name) const
    throw (std::runtime_error);

  /**
   * Gibt den Wert der Variablen mit Namen name als bool zurueck.
   * @param name Name der Variablen
   * @param defaultValue Wert der zurückgegeben wird, falls die Variable
   *        nicht vorkommt,
   *                     oder keinen bool wert hat (true, false).
   * @return true falls name="true" in der struct vorkommt,
   *         false falls name="false" vorkommt.
   */
  bool getBoolValue(const std::string& name, bool defaultValue) const;    

  /**
   * Gibt den Wert der Variablen mit Namen name als double zurueck.
   * @param name Name der Variablen
   * @return die Zahl x falls name="x" in der struct vorkommt.
   * @throw std::runtime_error Falls die Variable nicht in der c-struct
   *         existiert oder keinen Zahlenwert hat.
   */
  double getDoubleValue(const std::string& name) const
    throw (std::runtime_error);

  /**
   * Gibt den Wert der Variablen mit Namen name als double zurueck.
   * @param name Name der Variablen
   * @param defaultValue Wert der zurückgegeben wird, falls die Variable
   *         nicht vorkommt, oder keinen numerischen wert hat.
   * @return die Zahl x falls name="x" in der struct vorkommt.
   */
  double getDoubleValue(const std::string& name, double defaultValue) const;

  /**
   * Gibt den Wert der Variablen mit Namen name als int zurueck.
   * @param name Name der Variablen
   * @return die Zahl x falls name="x" in der struct vorkommt.
   * @throw std::runtime_error Falls die Variable nicht in der c-struct
   *         existiert oder keinen Zahlenwert hat.
   */
  int getIntValue(const std::string& name) const
    throw (std::runtime_error);

  /**
   * Gibt den Wert der Variablen mit Namen name als int zurueck.
   * @param name Name der Variablen
   * @param defaultValue Wert der zurückgegeben wird, falls die Variable nicht vorkommt,
   *                     oder keinen numerischen wert hat.
   * @return die Zahl x falls name="x" in der struct vorkommt.
   */
  int getIntValue(const std::string& name, int defaultValue) const;    

  /**
   * Gibt den Wert der Variablen mit Namen name als string zurueck.
   * @param name Name der Variablen
   * @return Den string s falls name=s in der struct vorkommt.
   * @throw std::runtime_error Falls die Variable nicht in der c-struct
   *         vorkommt.
   */
  std::string getStringValue(const std::string& name) const
    throw (std::runtime_error);

  /**
   * Gibt den Wert der Variablen mit Namen name als string zurueck.
   * @param name Name der Variablen
   * @param defaultValue Wert der zurückgegeben wird, falls die Variable nicht vorkommt.
   * @return Den string s falls name=s in der struct vorkommt.
   */
  std::string getStringValue(const std::string& name, const std::string& defaultValue) const;

  std::map<std::string,std::string> getMap() const;

  void serialize(std::ostream&) const;

 private:
  ConfigMap m_values;
  std::string m_name;

  // the default implementation should work
  //  StructReader(const StructReader&); // nicht impl.
  //  const StructReader& operator=(const StructReader&); // nicht impl.

  bool find(const std::string& name, std::string& value) const;
};

} // end of namespace utils

#endif
