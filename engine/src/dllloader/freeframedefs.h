#ifndef INCLUDED_FREE_FRAME_DEFS_H
#define INCLUDED_FREE_FRAME_DEFS_H

#include "basic_types.h"

namespace dllloader
{

  class FreeFrameDefs
  {

  public:

    enum PluginType { FF_EFFECT = 0 };

    enum RetValue { FF_FAIL = 0xFFFFFFFF, FF_SUCCESS = 0 };

    enum BoolValue { FF_TRUE = 1, FF_FALSE = 0 };

    enum Opcode { FF_GETINFO = 0, FF_INITIALISE = 1, FF_DEINITIALISE = 2,
                   FF_PROCESSFRAME = 3, FF_GETNUMPARAMETERS = 4,
                   FF_GETPARAMETERNAME = 5, FF_GETPARAMETERDEFAULT = 6,
                   FF_GETPARAMETERDISPLAY = 7, FF_SETPARAMETER = 8,
                   FF_GETPARAMETER = 9, FF_GETPLUGINCAPS = 10 };

    enum Caps { FF_16BPP = 0, FF_24BPP = 1, FF_32BPP = 2};

    typedef struct PlugInfoStructTag {
      uint_32  APIMajorVersion;
      uint_32  APIMinorVersion;
      char   uniqueID[4];     // 4 chars uniqueID - not null terminated
      char   pluginName[16];  // 16 chars plugin friendly name 
      // - not null terminated
      uint_32  pluginType;      // Effect or source
    } PlugInfoStruct;

    typedef struct VideoInfoStructTag {
      uint_32 frameWidth;       // width of frame in pixels
      uint_32 frameHeight;      // height of frame in pixels
      uint_32 bitDepth;         // enumerated indicator of bit depth of video 
      // 0 = 16 bit 5-6-5   1 = 24bit packed   2 = 32bit
    } VideoInfoStruct;

    typedef struct SetParameterStructTag {
      uint_32 index;
      float value;
    } SetParameterStruct;

    typedef union plugMainUnionTag {
      uint_32 ivalue;
      float fvalue;
      VideoInfoStruct *VISvalue;
      PlugInfoStruct *PISvalue;
      char *svalue;
    } plugMainUnion;
 
    typedef plugMainUnion (*plugMainT)(Opcode opcode,
                                       uint_32 param,
                                       uint_32 unused);
  };
}

#endif
