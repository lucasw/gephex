#include "freeframeloader.h"

#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "utils/sharedlibrary.h"
#include "freeframedefs.h"

#include "metamodule.h"
#include "module.h"

//TODO: -implement update
//      -enable patching 

namespace dllloader
{
  // for information that is shared among modules of one plugin type
  // TODO: if engine ever becomes multithreaded, access to SharedInfo
  // must get locked!
  class SharedInfo
  {
  public:
    SharedInfo(int width, int height)
      : m_width(width), m_height(height) {}

    void setResolution(int width, int height)
    {
      m_width  = width;
      m_height = height;
    }

    int height() const
    {
      return m_height;
    }

    int width() const
    {
      return m_width;
    }

  private:
    int m_width;
    int m_height;
  };

  class FreeFrameMetaModule : public MetaModule
  {
  public:
    FreeFrameMetaModule(FreeFrameDefs::plugMainT plugMain,
                        utils::ILogger& logger);

    ~FreeFrameMetaModule();

    Module* createModule();

    std::string getInfo() const;

    std::string getSpec() const;
    std::string getInputSpec(int index) const;
    std::string getOutputSpec(int index) const;

    void* getInputAttributes(int index) const;

  private:
    FreeFrameDefs::plugMainT m_plugMain;
    int m_numParams;
    std::string m_infoString;
    std::string m_specString;
    std::string m_paramSpec; 
    std::string m_fbSpec;
    std::string m_outSpec;

    SharedInfo m_sharedInfo;
  };

  class FreeFrameModule : public Module
  {
  public:
    FreeFrameModule(FreeFrameDefs::plugMainT plugMain,
                    int numParams,
                    SharedInfo& metaInfo);

    ~FreeFrameModule();

    void setInput(int index, void* type);
    void setOutput(int index, void* type);

    void update();
	
    void strongDependenciesCalculated(int** neededIns);
    void getPatchLayout(int** out2in );

  private:
    FreeFrameDefs::plugMainT m_plugMain;
    int m_numParams;
    // all modules of one plugin share a common info block
    SharedInfo& m_sharedInfo;
    
    uint_32* m_frb;

    FreeFrameDefs::VideoInfoStruct m_videoInfo;
  };


  MetaModule*
  FreeFrameLoader::loadPlugin(const utils::SharedLibrary& sl,
                              utils::ILogger& logger)
  {
    FreeFrameDefs::plugMainT plugMain 
      = (FreeFrameDefs::plugMainT) sl.loadSymbol("plugMain");

    if (!plugMain)
      return 0;

    try
      {
        MetaModule* m = new FreeFrameMetaModule(plugMain, logger);
        return m;
      }
    catch (std::runtime_error& e)
      {
        std::cout << e.what() << std::endl;
        return 0;
      }
  }


  // returns number of parameters
  int evalMetaInfo(FreeFrameDefs::plugMainT plugMain,
                   std::string& infoString,
                   std::string& specString,
                   std::string& paramSpec,
                   std::string& fbSpec,
                   std::string& outSpec);

  /***************************************************************************/

  FreeFrameMetaModule::FreeFrameMetaModule(FreeFrameDefs::plugMainT plugMain,
                                           utils::ILogger& logger)
    : MetaModule(logger), m_plugMain(plugMain), m_sharedInfo(-1, -1)
  {
    m_numParams = evalMetaInfo(m_plugMain, m_infoString, m_specString,
                               m_paramSpec, m_fbSpec, m_outSpec);
  }

  FreeFrameMetaModule::~FreeFrameMetaModule()
  {
  
  }

  Module* FreeFrameMetaModule::createModule()
  {
    return new FreeFrameModule(m_plugMain, m_numParams,
                               m_sharedInfo);
  }

  std::string FreeFrameMetaModule::getInfo() const
  {
    return m_infoString;
  }

  std::string FreeFrameMetaModule::getSpec() const
  {
    return m_specString;
  }

  std::string FreeFrameMetaModule::getInputSpec(int index) const
  {
    if (index < m_numParams)
      return m_paramSpec;
    else if (index == m_numParams)
      return m_fbSpec;
    else
      return "";
  }

  std::string FreeFrameMetaModule::getOutputSpec(int index) const
  {
    if (index == 0)
      return m_outSpec;
    else
      return "";
  }

  void* FreeFrameMetaModule::getInputAttributes(int index) const
  {
    return 0;
  }

  /***************************************************************************/

  FreeFrameModule::FreeFrameModule(FreeFrameDefs::plugMainT plugMain,
                                   int numParams,
                                   SharedInfo& sharedInfo)
    : m_plugMain(plugMain), m_numParams(numParams), m_sharedInfo(sharedInfo),
      m_frb(0)
  {
  }

  FreeFrameModule::~FreeFrameModule()
  {
  }

  void FreeFrameModule::setInput(int index, void* type)
  {
    if (index < 0 || index > m_numParams)
      return;

    if (index < m_numParams)
      {
        FreeFrameDefs::SetParameterStruct param;        
        param.index = index;
        param.value = 1; //TODO

        m_plugMain(FreeFrameDefs::FF_SETPARAMETER, (uint_32) &param, 0);
      }
    else
      {
        m_videoInfo.frameWidth  = 640; //TODO
        m_videoInfo.frameHeight = 480; //TODO
        m_videoInfo.bitDepth    = FreeFrameDefs::FF_32BPP;
        m_frb                   = 0; //TODO
      }
  }

  void FreeFrameModule::setOutput(int index, void* type)
  {
  }

  void FreeFrameModule::update()
  {

  }
	
  void FreeFrameModule::strongDependenciesCalculated(int** neededIns)
  {
    assert(!"This should never be called!");
  }
 
  void FreeFrameModule::getPatchLayout(int** out2in)
  {
    assert(!"This should never be called!");
  }

  /***************************************************************************/

  std::string trim(const std::string& s)
  {
    std::string::size_type pos1 = s.find_first_not_of(" ");
    std::string::size_type pos2 = s.find_last_not_of(" ");

    if (pos1 == std::string::npos || pos2 == std::string::npos)
      {
        return "";
      }
    else
      return s.substr(pos1, pos2 - pos1);
  }

  std::string remove_ws(const std::string& s)
  {
    std::string st = trim(s);
    for (int i = 0; i < st.length(); ++i)
      {
        if (st[i] == ' ')
          st[i] = '_';
      }
  }

  void buildInfoSpec(const FreeFrameDefs::PlugInfoStruct& info,
                     const std::vector<std::string>& paramNames,
                     const std::vector<float>& paramDefaults,
                     std::string& infoString, std::string& specString,
                     std::string& paramSpec,
                     std::string& fbSpec, std::string& outSpec)
  {
    std::ostringstream inf;
    inf << "info { name=[" 
        << std::string(info.pluginName,16) << "] group = [FreeFrame] " 
        << "inputs=[";

    inf << paramNames.size();
    for (int i = 0; i < paramNames.size(); ++i)
      {
        inf << " " << remove_ws(std::string(paramNames[i], 16));
      }

    if (info.pluginType == FreeFrameDefs::FF_EFFECT)
      inf << " Bild";

    inf <<" ] outputs=[1 Bild ] type=xpm } ";

    infoString = inf.str();

    std::ostringstream spec;

    spec << "mod_spec { name=[mod_ffr_" 
         << remove_ws(std::string(info.pluginName,16))
         << "] number_of_inputs=[" << paramNames.size()
         << "] number_of_outputs=[1] deterministic=[false] }";

    specString = spec.str();

    paramSpec = "input_spec { type=typ_NumberType const=true strong_dependency=true  } ";

    fbSpec = "input_spec { type=typ_FrameBufferType const=false strong_dependency=true  } ";

    outSpec = "output_spec { type=typ_FrameBufferType } ";

  }

  int evalMetaInfo(FreeFrameDefs::plugMainT plugMain,
                   std::string& infoString,
                   std::string& specString,
                   std::string& paramSpec,
                   std::string& fbSpec,
                   std::string& outSpec)
  {
    FreeFrameDefs::plugMainUnion ret;

    ret = plugMain(FreeFrameDefs::FF_GETINFO, 0, 0);

    if (ret.ivalue == FreeFrameDefs::FF_FAIL)
      throw std::runtime_error("GETINFO failed");

    FreeFrameDefs::PlugInfoStruct* info = ret.PISvalue;

    if (plugMain(FreeFrameDefs::FF_GETPLUGINCAPS,
                 FreeFrameDefs::FF_32BPP, 0).ivalue == FreeFrameDefs::FF_FALSE)
      throw std::runtime_error("Plugin can't do 32 bpp");

    int numParams;

    ret = plugMain(FreeFrameDefs::FF_GETNUMPARAMETERS, 0, 0);
    if (ret.ivalue == FreeFrameDefs::FF_FAIL)
      {
        std::cout << "Could not get number of parameters!" << std::endl;
        numParams = 0;
      }
    else
      numParams = ret.ivalue;

    std::vector<std::string> paramNames(numParams);
    std::vector<float> paramDefaults(numParams);

    for (int i = 0; i < numParams; ++i)
      {
        std::string name = "unnamed";
        ret = plugMain(FreeFrameDefs::FF_GETPARAMETERNAME, i, 0);
        if (ret.ivalue == FreeFrameDefs::FF_FAIL)
          {
            std::cout << "Could not get param name for param #"
                      << i << std::endl;
          }
        else
          name = std::string(ret.svalue, 16);

        float def = 0;
        ret = plugMain(FreeFrameDefs::FF_GETPARAMETERDEFAULT, i, 0);
        if (ret.ivalue == FreeFrameDefs::FF_FAIL)
          {
            std::cout << "Could not get default value for param #"
                      << i << std::endl;
          }
        def = ret.fvalue;

        paramNames[i]    = name;
        paramDefaults[i] = def;
      }

    buildInfoSpec(*info,
                  paramNames,
                  paramDefaults,
                  infoString,
                  specString,
                  paramSpec,
                  fbSpec,
                  outSpec);

    return numParams;
  }

}
