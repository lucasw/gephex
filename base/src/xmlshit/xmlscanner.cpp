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

#include "xmlscanner.h"
#include "xmllistener.h"
#include "../../utils/src/stringtokenizer.h"

#include <iostream>
#include <stdexcept>
#include <string>


XMLFileScanner::XMLFileScanner(XMLTokenListener& l_):l(l_),pos(0)
{}

void XMLFileScanner::scanInfoSection(std::string& text)
{
  StringTokenizer st(text);
  std::string delim("\n\r\t ");
  std::string token;

  //TODO derzeit wird nur name des moduls eingelesen...müsste aber eigentlich reichen
  token = st.next(delim); //moduleinfos
  token = st.next(delim); //first moduleinfo
  while(token != "/moduleinfos")
    {
      if(token != "moduleinfo")
	throw std::runtime_error("Error in Format in moduleinfo section discovered..");

      token = st.next(delim);		//module_identifier

      std::string mi(token.substr(1, token.length()-2));
      l.scannedModuleInfo(mi); //notify listener

      while(token != "/moduleinfo")
	{
	  token = st.next(delim);
	  if(token == "moduleinfo")
	    throw std::runtime_error("Error in Format in modulinfo section discovered...closing tag missing...");
	}
      token = st.next(delim); //moduleinfo or /moduleinfos
    }
	
	
}


/**
* Scanned eine node section, d.h. von <nodes> bis </nodes> und gibt 
* die resultate an den listener weiter, die anderen scanBlaBlaSection arbeiten
* analog
**/
void XMLFileScanner::scanNodeSection(std::string& text)
{
  StringTokenizer st(text);
  std::string delim(" \n");
  std::string token;
  std::string nodeString;

  token = st.next(delim); //nodes
  token = st.next(delim);
  while(token != "/nodes")
    {
      if(token != "node") 
	throw std::runtime_error("Wrong Format in Node Section discoverd..\n");
		
      while(token != "/node")
	{			
	  token = st.next(delim);
	  //can't find another <node> before a </node>
	  if(token=="node") 
	    throw std::runtime_error("Wrong Format in Node Section discoverd..closing tag missing\n");

	  nodeString += token;
	  nodeString += " ";
	}
      l.scannedNode(nodeString, pos);  //notify listener
      nodeString = "";			//clean string
      token = st.next(delim);
      ++pos;
    }
	
	
  //std::cout <<text<<"\n";
}

void XMLFileScanner::scanConnectionSection(std::string& text)
{
  StringTokenizer st(text);
  std::string delim(" \n");
  std::string token;
  std::string connectionString;
	
  token = st.next(delim); //connections
  token = st.next(delim);
  while(token != "/connections")
    {
      if(token != "connection") 
	throw std::runtime_error("Wrong Format in connection Section discoverd..\n");
		
      while(token != "/connection")
	{	
	  token = st.next(delim);
	  if(token=="connection") 
	    throw std::runtime_error("Wrong Format in connection Section discoverd..closing tag missing\n");
			
	  connectionString += token;
	  connectionString += " ";
	}

      l.scannedConnection(connectionString);
      connectionString = "";

      token = st.next(delim);
    }
  //std::cout <<text<<"\n";
}

void XMLFileScanner::scanCtrlSection(std::string& text)
{
  StringTokenizer st(text);
  std::string delim(" \n");
  std::string token;
  std::string controlString;
	
  token = st.next(delim); //controls
  token = st.next(delim);
  while(token != "/controls")
    {
      if(token != "control") 
	throw std::runtime_error("Wrong Format in control Section discoverd..\n");
		
      while(token != "/control")
	{	
	  token = st.next(delim);
	  if(token=="control") 
	    throw std::runtime_error("Wrong Format in control Section discoverd..closing tag missing\n");
			
	  controlString += token;
	  controlString += " ";
	}

      l.scannedControl(controlString);	
      controlString = "";

      token = st.next(delim);
    }
	
	
  //std::cout <<text<<"\n";
}
	
/**
* Scans a whole fucking xml-style graph-model-file...raaaaa...
**/
void XMLFileScanner::scan(std::string& text)
{
  StringTokenizer st(text);
  std::string delim("<>");
  std::string token;
  std::string section;


  //token = st.next(delim); // <
  token = st.next(delim); // <tag>

  if(token == "model")
    {
      token = st.next(delim); // <model> /n <
      token = st.next(delim); // <modelinfos>
		
      if(token == "moduleinfos")
	{
	  section += "moduleinfos\n";
	  token = st.next(delim);
	  while(token!= "/moduleinfos" )
	    {
	      token = st.next(delim); //cut "\n"
	      section += token;
	    }
	  scanInfoSection(section);			
	} else {
	  throw std::runtime_error("File has wrong format...section moduleinfos");
	}
      //reset section string
      section = "";
      token = st.next(delim);
      token = st.next(delim);
      if(token == "nodes")
	{
	  section += "nodes\n";
	  token = st.next(delim);
	  while(token != "/nodes")
	    {
	      token = st.next(delim); //cut "\n"
	      section += token;
	    }
	  scanNodeSection(section);
	} else {
	  throw std::runtime_error("File has wrong format...section nodes");
	}
      section = "";
      token = st.next(delim);
      token = st.next(delim);
      if(token == "controls")
	{
	  section += "controls\n";
	  token = st.next(delim);
	  while(token != "/controls")
	    {
	      token = st.next(delim);
	      section += token;
	    }
	  scanCtrlSection(section);
	} 
      else 
	{
	  throw std::runtime_error("File has wrong format...section controls");
	}
      section = "";
      token = st.next(delim);
      token = st.next(delim);
      if(token == "connections")
	{
	  section += "connections\n";
	  token = st.next(delim);
	  while(token != "/connections")
	    {
	      token = st.next(delim);
	      section += token;
	    }
	  scanConnectionSection(section);
	} 
      else 
	{
	  std::string msg = "File has wrong format...section connections. ";
	  msg += token;
	  throw std::runtime_error(msg.c_str());
	}

      token = st.next(delim);
      token = st.next(delim);
      if(token != "/model")
	throw std::runtime_error("File has a wrong finishing tag...wrong format");
    } 
  else 
    {
      throw std::runtime_error("This is no Ge-Phex Graph file...go fuck your dog!!!");
    }
}
