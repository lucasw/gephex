#include "structscannertest.h"

#include <map>

#include "structscanner.h"

/*---------------------------------------------------------------------------*/

class DummyListener : public utils::IStructTokenListener
{
public:
  std::string m_name;
  std::map<std::string,std::string> nam2val;

  virtual ~DummyListener() {} //to shut up the compiler

  virtual void beginStruct()
  {
  }

  virtual void endStruct()
  {
  }

  virtual void scannedStructName(const std::string& name)
  {
    m_name = name;
  }

  virtual void scannedPair(const std::string& name,
			   const std::string& value,int )
  {
    nam2val[name] = value;
  }
};

/*---------------------------------------------------------------------------*/

StructScannerTest::StructScannerTest()
  : EasyTest("StructScannerTest","")
{
}

StructScannerTest::~StructScannerTest()
{
}

void StructScannerTest::pre() throw(std::runtime_error)
{
}

static void testDummy(DummyListener& dummy,std::string name,
		      std::string n1, std::string v1,
		      std::string n2, std::string v2)
{
  if (dummy.m_name != name)
    throw std::runtime_error("Strukturname falsch");

  if (dummy.nam2val[n1] != v1)
    {
      std::string msg = "Strukturwert falsch\n";
      msg += "name = " + n1 + "\nwert (soll): " + v1 
	+ "\nwert (ist): " + dummy.nam2val[n1];
      throw std::runtime_error(msg.c_str());
    }

  if (dummy.nam2val[n2] != v2)
    {
      std::string msg = "Strukturwert falsch!\n";
      msg += "name = " + n2 + "\nwert (soll): " + v2 
	+ "\nwert (ist): " + dummy.nam2val[n2];
      throw std::runtime_error(msg.c_str());
    }
}

void StructScannerTest::run() throw(std::runtime_error)
{
  DummyListener dl;
  utils::StructScanner sScanner(dl);

  sScanner.scan("info { name=Schrift group=Schrifteffekte inputs=[8 Text{widget_type=text_edit; hidden=true; default_value=Scrolltext;} "
  "Schriftart{widget_type=font_selector; hidden=true;} Farbe{widget_type=color_selector; hidden=true;} Position X-Rotation{widget_type=number_selector; hidden=true; higher_bound=20; lower_bound=0;}"
  " Y-Rotation{widget_type=number_selector; hidden=true; higher_bound=20; lower_bound=0;} Z-Rotation{widget_type=number_selector; hidden=true; higher_bound=20; lower_bound=0;}"
		" Bild] outputs=[1 Bild] type=xpm }");

  testDummy(dl,"info","inputs","8 Text{widget_type=text_edit; hidden=true; default_value=Scrolltext;} "
  "Schriftart{widget_type=font_selector; hidden=true;} Farbe{widget_type=color_selector; hidden=true;} Position X-Rotation{widget_type=number_selector; hidden=true; higher_bound=20; lower_bound=0;}"
	    " Y-Rotation{widget_type=number_selector; hidden=true; higher_bound=20; lower_bound=0;} Z-Rotation{widget_type=number_selector; hidden=true; higher_bound=20; lower_bound=0;} Bild","group","Schrifteffekte");

  sScanner.scan("info { name=Schrift group=Schrifteffekte inputs=[4 Text{widget_type=text_edit; hidden=false; default_value=Scrolltext;} "
                   "Schriftart{widget_type=font_selector; hidden=true;} Geschwindigkeit{widget_type=number_selector; lower_bound=0; higher_bound=20; hidden=true;} Bild] outputs=[1 Bild] type=xpm }"); 

  testDummy(dl,"info","inputs","4 Text{widget_type=text_edit; hidden=false; default_value=Scrolltext;} "
                   "Schriftart{widget_type=font_selector; hidden=true;} Geschwindigkeit{widget_type=number_selector; lower_bound=0; higher_bound=20; hidden=true;} Bild","outputs","1 Bild");

  sScanner.scan("Text{widget_type=text_edit; hidden=false; default_value=Scrolltext;} ");
                  
  testDummy(dl,"Text","widget_type","text_edit","hidden","false");

  sScanner.scan("Schriftart{widget_type=font_selector; hidden=true;}");
  testDummy(dl,"Schriftart","widget_type","font_selector","hidden","true");

  sScanner.scan("Geschwindigkeit{widget_type=number_selector; lower_bound=0; higher_bound=20; hidden=true;}");
  testDummy(dl,"Geschwindigkeit","widget_type","number_selector","lower_bound","0");

  sScanner.scan("info { name=[Bild Lade Einrichtung]; "
		              "inputs=[1 Dateiname{widget_type=file_selector; "
					                      "hidden=true; file_mask=*.bmp; "
					   		  			  "file_mask_name=Bild; }]; "
					  "outputs=[1 Bild]; type=xpm; }");
  testDummy(dl,"info","inputs","1 Dateiname{widget_type=file_selector; "
					                      "hidden=true; file_mask=*.bmp; "
					   		  			  "file_mask_name=Bild; }","outputs","1 Bild");


  sScanner.scan("bell{hund=[Hunde sind so] bell=[wie sie sind] }");
  testDummy(dl,"bell","hund","Hunde sind so","bell","wie sie sind");

  sScanner.scan("doof { 1=2; 3=4; }");
  testDummy(dl,"doof","1","2","3","4");
  sScanner.scan("dumm{ rechts=links links=rechts }");
  testDummy(dl,"dumm","rechts","links","links","rechts");
  sScanner.scan("otto{a=b c=d }");
  testDummy(dl,"otto","a","b","c","d");
  sScanner.scan("kort {kirt=kart kert=kwrt}");
  testDummy(dl,"kort","kirt","kart","kert","kwrt");
  sScanner.scan("bell{hund=, bell=doch!}");
  testDummy(dl,"bell","hund",",","bell","doch!");

  

  
}

void StructScannerTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
