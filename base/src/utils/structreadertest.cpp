#include "structreadertest.h"

#include "structreader.h"
#include <map>

/*---------------------------------------------------------------------------*/

StructReaderTest::StructReaderTest()
  : EasyTest("StructReaderTest","")
{
}

StructReaderTest::~StructReaderTest()
{
}

void StructReaderTest::pre() throw(std::runtime_error)
{
}

void StructReaderTest::run() throw(std::runtime_error)
{
  std::string structure = "test { var1=1; var2=Hallo; var3=true; }";
  utils::StructReader reader(structure);

  if (reader.getName() != "test")
    throw std::runtime_error("Name ist falsch erkannt");

  if (reader.getIntValue("var1") != 1)
    throw std::runtime_error("Int Variable falsch");

  if (reader.getStringValue("var2") != "Hallo")
    throw std::runtime_error("String Variable falsch");

  if (reader.getBoolValue("var3") != true)
    throw std::runtime_error("Bool Variable falsch");

  bool exception = true;
  try {
    int tmp =  reader.getIntValue("var3"); // exception shoul be thrown
    exception = false;
  }
  catch (std::runtime_error) {}

  if (!exception) 
    throw std::runtime_error("Typueberpruefung fehlgeschlagen");
}

void StructReaderTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
