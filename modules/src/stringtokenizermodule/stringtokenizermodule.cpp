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

#include "stringtokenizermodule.h"

#include <string>
#include <sstream>
#include <vector>

#include <cassert>

static logT s_log;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  if (my == 0)
  {
	  s_log(0, "Could not allocate memory for MyInstance struct\n");
	  return 0;
  }

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  const char delimiter =',';

  std::string input = inst->in_string->text;
  size_t nr = trim_int(inst->in_entry->number,1,1000) - 1;

  std::istringstream ist(input);
  
  std::vector<std::string> tokens;

  std::string w;
  while (std::getline(ist, w, delimiter)) 
    tokens.push_back(w);

  inst->out_len->number = tokens.size();

  if (tokens.empty())
    {
      string_charAssign(inst->out_token, "");	  
    }
  else
    {
      nr %= tokens.size();
      assert(0 <= nr && nr < tokens.size());
      string_charAssign(inst->out_token, tokens[nr].c_str());
    }
}


