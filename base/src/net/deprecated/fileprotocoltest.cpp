#include "fileprotocoltest.h"

#include <fstream>

#include "fileprotocol.h"
#include "inetprotocol.h"

#include "utils/buffer.h"

#include "block.h"


class MyProt : public net::INetProtocol
{
public:
  virtual void sendCommand(const char command[4],const utils::Buffer& buf)
  {
    m_cip->commandReceived(command,buf);
  }

  virtual void setCommandInterpreter(net::ICommandInterpreter& cip)
  {
    m_cip = &cip;
  }

private:
  net::ICommandInterpreter* m_cip;
};

class FileReceiver : public net::ICommandInterpreter
{
public:
  FileReceiver()
    : m_data(0), m_len(0)
  {
  }

  virtual void commandReceived(const std::string& command,
			       const utils::Buffer& buf)
  {
    std::ifstream f(reinterpret_cast<const char*>(buf.getPtr()),
		    std::ios::in|std::ios::binary);
    if (!f)
      {
	m_data = 0;
	m_len = 0;
      }
    else
      {
	int l = f.tellg();
	f.seekg (0, std::ios::end);
	int m = f.tellg();
	f.seekg(0,std::ios::beg);
	m_len = m - l;
	if (m_data != 0)
	  delete[] m_data;
	m_data = new unsigned char[m_len];
	f.read((char*)m_data,m_len);
	if (!f)
	  {
	    m_data = 0;
	    m_len = 0;
	  }
      }
  }
  
  

  unsigned char* m_data;
  int m_len;
};

FileProtocolTest::FileProtocolTest()
  : EasyTest("FileProtocol","")
{
}

FileProtocolTest::~FileProtocolTest()
{
}

void FileProtocolTest::pre() throw(std::runtime_error)
{

}

void FileProtocolTest::run() throw(std::runtime_error)
{
  static const char* FILE_NAME = "/tmp/filetest.out";
  std::ofstream of;

  MyProt mp;
  FileReceiver fr;
  net::FileProtocol fp(mp,fr);
  mp.setCommandInterpreter(fp);


  for (int len = 1; len < 1024*1024*8; len *= 2)
    {
      std::cerr << ".";
      std::cerr.flush();

      of.open(FILE_NAME,std::ios::out|std::ios::trunc|std::ios::binary);
      if (!of)
	throw std::runtime_error("Konnte Datei nicht oeffnen!");

      unsigned char* data = createRandomBlock(len);
      of.write((char*)data,len);
      of.close();

      fp.send(FILE_NAME);

      if (!compareBlocks(data,len,fr.m_data,fr.m_len))
	{
	  std::string msg = "Fehler: ";
	  msg += reinterpret_cast<char*>(data);
	  msg += " != ";
	  msg += reinterpret_cast<char*>(fr.m_data);
	  throw std::runtime_error(msg.c_str());
	}

      delete[] data;
    }

}

void FileProtocolTest::post() throw(std::runtime_error)
{
}

