#include "filesystemtest.h"

#include <iostream>

#include "filesystem.h"


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
	std::list<utils::DirEntry> l;
	utils::FileSystem::listDir("/home/mistkerl",l);

	for (std::list<utils::DirEntry>::const_iterator i = l.begin();
		 i != l.end(); ++i)
	{
		std::cout << i->getName() << "\t\t" << i->getSizeInBytes() << std::endl;
	}
}

void FileSystemTest::post() throw(std::runtime_error)
{
}
