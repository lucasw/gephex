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

#include "moduleclassmodel.h"

#include <sstream>
#include <cassert>

//TODO
#include <iostream>

#include "imoduleclassview.h"
#include "moduleinfo.h"
#include "xpm.h"

#include "utils/structreader.h"
#include "utils/stringtokenizer.h"
#include "utils/buffer.h"

namespace gui
{

  namespace
  {
    std::string mySubstr(const std::string& t,
			 std::string::size_type pos1,
			 std::string::size_type pos2)
    {
      assert( pos1 <= t.length() && pos2 <= t.length() );
		
      std::string result;
      for (std::string::size_type i = pos1; i < pos2; ++i)
	{
	  result += t[i];
	}
		
      return result;
    }
	
    void processInfoStruct(utils::StringTokenizer& st, PlugInfo& pi)
    {
      const std::string& str = st.getString();
      std::string::size_type pos1 = st.getPos();
      if (pos1 == std::string::npos)
	{
	  std::ostringstream os;
	  os << "st is completely finished at processInfoStruct" << std::endl;
	  os << "str = " << str << std::endl;
	  std::string msg = os.str();
	  throw std::runtime_error(msg.c_str());
	}
		
      std::string name = st.next(" {");
      std::string::size_type pos = st.getPos();
      /*      if (pos == std::string::npos)
	{
	  std::ostringstream os;
	  os << "st is ... finished at processInfoStruct" << std::endl;
	  os << "str = " << str << std::endl;
	  os << "name = " << name << std::endl;
	  std::string msg = os.str();
	  throw std::runtime_error(msg.c_str());
	  }*/

		
      pos = str.find_first_not_of(" \t\n",pos);
      /*      if (pos == std::string::npos)
	{
	  std::ostringstream os;
	  os << "st is ... finished at processInfoStruct" << std::endl;
	  os << "str = " << str << std::endl;
	  os << "name = " << name << std::endl;
	  std::string msg = os.str();
	  throw std::runtime_error(msg.c_str());
	  }*/
		
		
      unsigned int iPos = name.find(':');
      if (iPos == std::string::npos)
	{
	  throw std::runtime_error("couldnt find : at processInfoStruct");
	}
      pi.type = mySubstr(name,iPos+1,name.length());
      pi.name = mySubstr(name,0,iPos);
		
      if (pos != std::string::npos && (str[pos] == '{' || str[pos-1] == '{'))
	{
	  //	const std::string& str = st.getString();
	  std::string::size_type pos2 = str.find('}',pos1);
	  if (pos2 == std::string::npos)
	    {	    
	      std::ostringstream os;
	      os << "couldnt find } at processInfoStruct" << std::endl;
	      os << " - str = " << str << std::endl;
	      os << " - pos = " << pos << std::endl;
	      os << " - pos1 = " << pos1 << std::endl;
	      std::string msg = os.str();
	    
	      throw std::runtime_error(msg.c_str());
	    }
	  std::string temp = mySubstr(str,pos1,pos2+1);
	  if (temp == "")
	    {
	      std::cerr << "Error at processInfoStruct!" << std::endl;
	      std::cerr << "str = " << str << std::endl;
	      std::cerr << "name = " << name << std::endl;
	      std::cerr << "pi.type = " << pi.type << std::endl;
	      std::cerr << "pi.name = " << pi.name << std::endl;
	      std::cerr << "pos = " << pos << std::endl;
	      std::cerr << "iPos = " << iPos << std::endl;
	      std::cerr << "pos1 = " << pos2 << std::endl;
	      std::cerr << "pos2 = " << pos2 << std::endl;
	      throw std::logic_error("nix");
	    }
	  utils::StructReader sr(temp);
	  pi.params = sr.getMap();
	  st.next("}");
	}
    }
	
	
    std::vector<PlugInfo> processArray(const std::string& s)
    {
      utils::StringTokenizer st(s);
		
      std::string ssize;
      ssize = st.next(" \t\n");
      std::istringstream os(ssize);
      int size;
      os >> size;
		
      std::vector<PlugInfo> ins(size);
      for (int i = 0; i < size; ++i)
	{
	  try {
	    processInfoStruct(st,ins[i]);
	  }
	  catch (std::logic_error&)
	    {
	      std::cerr << "Error while processing <" << 
		s << ">, i = " << i << std::endl;
	      throw;
	    }
	}
		
      return ins;
    }
	
    ModuleInfo parseModuleInfo(const utils::Buffer& buf)
    {		
      utils::StructReader sr(reinterpret_cast<const char*>(buf.getPtr()));
      try
	{
	  std::string name = sr.getStringValue("gui_name");
	  std::string identifier = sr.getStringValue("identifier");
	  std::string group = sr.getStringValue("group");
	  std::string inputs = sr.getStringValue("inputs");
	  std::string outputs = sr.getStringValue("outputs");
	  std::string moduleType = sr.getStringValue("type");

	  try {
	    std::vector<PlugInfo> ins = processArray(inputs);
	    std::vector<PlugInfo> outs = processArray(outputs);
			
	    if (moduleType == "xpm")
	      {
		const char* ptr = reinterpret_cast<const char*>(buf.getPtr());
		const char* offset = ptr + strlen(ptr) + 1;
		int newLen = buf.getLen() - strlen(ptr) - 1;
		utils::AutoPtr<Xpm> xpm(new Xpm(offset,newLen));
	      
		return ModuleInfo(identifier,name,group,ins,outs,xpm);
	      }
	    else
	      {
		throw std::runtime_error("MUIltkj");
	      }
	  
	  }
	  catch (std::logic_error&)
	    {
	      std::cerr << "Buffer = <" << buf.getPtr() << ">" << std::endl;
	    }
	}
      catch (std::runtime_error& e)
	{
	  std::string msg = "Fehler beim Parsen der ModulInfo: ";
	  msg += e.what();
	  throw std::runtime_error(msg.c_str());
	}
    }
  }

  ModuleClassModel::~ModuleClassModel()
  {
  }
	
  void ModuleClassModel::registerModuleClassView(IModuleClassView& v)
  {
    views.push_back(&v);
  }
	
  void ModuleClassModel::unregisterModuleClassViews()
  {
    views.clear();
  }
	
  void ModuleClassModel::moduleClassLoaded(const std::string& moduleClassName,
					   const utils::Buffer& buf)
  {
    ModuleInfo mi = parseModuleInfo(buf);
		
    for (std::list<IModuleClassView*>::const_iterator it = views.begin();
	 it != views.end(); ++it)
      {
	(*it)->moduleClassLoaded(moduleClassName,mi);
      }
  }
	
  void ModuleClassModel::moduleClassUnloaded(const std::string& moduleClassName)
  {
    for (std::list<IModuleClassView*>::const_iterator it = views.begin();
	 it != views.end(); ++it)
      {
	(*it)->moduleClassUnloaded(moduleClassName);
      }
  }
	
  void ModuleClassModel::syncStarted()
  {
    for (std::list<IModuleClassView*>::const_iterator it = views.begin();
	 it != views.end(); ++it)
      {
	(*it)->syncStarted();
      }
  }
	
  void ModuleClassModel::syncFinished()
  {
    for (std::list<IModuleClassView*>::const_iterator it = views.begin();
	 it != views.end(); ++it)
      {
	(*it)->syncFinished();
      }
  }
	
} // end of namespace
