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

#include "filesystemtest.h"

#include <iostream>

#include "filesystem.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif


std::string FileSystemTest::getName() const
{
	return "FileSystemTest";
}

std::string FileSystemTest::getDescription() const
{
	return "";
}

void FileSystemTest::pre() throw(std::runtime_error)
{
}

void FileSystemTest::run() throw(std::runtime_error)
{
	/*std::list<utils::DirEntry> l;
	utils::FileSystem::listDir("/home/mistkerl",l);

	for (std::list<utils::DirEntry>::const_iterator i = l.begin();
		 i != l.end(); ++i)
	{
		std::cout << i->getName() << "\t\t" << i->getSizeInBytes() << std::endl;
	}*/

	std::string fileThatExists = "";
	std::string fileThatIsMissing = "";
#if defined(OS_WIN32)
	fileThatExists = "C:\\autoexec.bat";
	//fileThatExists = "C:\\code\\";
	fileThatIsMissing = "C:\\autoexec.bat.exe.com";
#elif defined(OS_LINUX)
	fileThatExists = "/etc";
	fileThatIsMissing = "/hosenFeilchen";
#endif

	if (fileThatExists != "" && fileThatIsMissing != "")
	{
		if (!utils::FileSystem::exists(fileThatExists))
			throw std::runtime_error("existing file not detected!");

		if (utils::FileSystem::exists(fileThatIsMissing))
			throw std::runtime_error("missing file detected as existing!");
	}
}

void FileSystemTest::post() throw(std::runtime_error)
{
}
