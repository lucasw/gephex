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
