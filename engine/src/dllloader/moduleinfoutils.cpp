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

#include "moduleinfoutils.h"
#ifdef WIN32
#include <string.h>
#endif

#include <cstring>
#include <sstream>
#include <cassert>

#include "c_moduletables.h"

#include "utils/stringtokenizer.h"
#include "utils/structreader.h"

#include "utils/buffer.h"


namespace {

  std::string processStruct(utils::StringTokenizer& st,
			    const std::string& type)
  {
    std::string result;
	
    std::string name = st.next(" {");
    std::string::size_type pos = st.getPos();
    const std::string& str = st.getString();

    pos = str.find_first_not_of(" \t\n",pos);

    std::string content;

    if (pos > 0 && pos < str.length() 
	&& str[pos-1] == '{')
      {
	content = st.next("}");

	//st.next(" \n\t");
      }

    //std::string content = st.next("}");

    result += name;
    result += ':';
    result += type;
    if (content != "")
      {
	result += " { ";
	result += content;
	result += " }";
      }
    result += ' ';

    return result;
  }


  std::string readVector(const std::string& array,
			 const std::vector<std::string>& types)
  {
    std::string newArray;

    utils::StringTokenizer st(array);

    std::string result;
 
    std::string ssize;
    ssize = st.next(" \n\t");
    result += ssize + ' ';

    std::string::size_type size;
    std::istringstream stmp(ssize);
    stmp >> size;

    if (size != types.size())
      {
	throw std::runtime_error("Falsche Arraygroesse bei getInfo.");
      }

    for (std::string::size_type i = 0; i < size; ++i)
      {
	result += processStruct(st,types[i]);
      }

    return result;
  }

  /*std::string readString(const std::string& text,
    std::string::size_type& p) const
    {
    if (text[0] == '\'')
    {
    std::string::size_type pos2 = text.find('\'',1);
    if (pos2 == std::string::npos)
    {
    throw std::runtime_error("Abschliessendes ' fehlt!");
    }

    p = pos2+1;
    return text.substr(1,pos2-1);
    }

    StringTokenizer st (text);
    std::string result = st.next(" \n\t");
    p = st.getPos();
    return result;
    }*/
}

namespace dllloader
{

  utils::Buffer ModuleInfo::enrichInfo(const char* data, int len,
				       const std::string& name,
				       const std::vector<std::string>&inNames,
				       const std::vector<std::string>&outNames)
  {
    utils::StructReader sr(data);

    std::string guiName = sr.getStringValue("name");

    std::string guiType = sr.getStringValue("type");

    std::string group = sr.getStringValue("group");

    std::string inputs = sr.getStringValue("inputs");

    std::string outputs = sr.getStringValue("outputs");
	
    std::string newInputs = readVector(inputs,inNames);
    std::string newOutputs = readVector(outputs,outNames);
  
    std::map<std::string,std::string> newMap;
    newMap["gui_name"] = guiName;
    newMap["identifier"] = name;
    newMap["group"] = group;
    newMap["inputs"] = newInputs;
    newMap["outputs"] = newOutputs;
    newMap["type"] = guiType;
    utils::StructReader sr2(newMap);
  
    std::ostringstream stream;
    sr2.serialize(stream);

    std::string info = stream.str();

    int size = strlen(data)+1;
    bool copyChunk = false;
    int m_len;
    if (size < len) 
      {
	// da haengen noch daten dran
	m_len = info.length() + 1 + (len - size);
	copyChunk = true;
      }
    else
      {
	m_len = info.length()+1;
      }

    unsigned char* m_data = new unsigned char[m_len];
    memcpy(m_data,info.c_str(),info.length()+1);

    if (copyChunk)
      {
	memcpy(m_data+info.length()+1,data+size,len-size);
      }

    return utils::Buffer(m_data, m_len, true);
  }

}

