#include "fileprotocol.h"

#include <fstream>
#include <cassert>

#include "inetprotocol.h"

#include "../utils/buffer.h"

namespace net
{

  FileProtocol::FileProtocol(INetProtocol& np, ICommandInterpreter& fileReceiver)
    : m_netProtocol(&np), m_fileReceiver(&fileReceiver)
  {
  }

  FileProtocol::~FileProtocol()
  {
  }

  std::string FileProtocol::getCommand() const
  {
    return "file";
  }

  static int getFileSize(std::ifstream& file)
  {
    int oldPos = file.tellg();
    file.seekg(0,std::ios::beg);
    int l = file.tellg();
    file.seekg (0, std::ios::end);
    int m = file.tellg();
	
    file.seekg(oldPos);
    return  m - l;
  }

  static int min(int a, int b)
  {
    return (a < b) ? a : b;
  }

  //TODO: plattformabhaengig!
  struct FileHeader
  {
    int file_size;
    int block_count;
    int block_number;
  };

  void FileProtocol::send(const std::string& filename)
    throw (std::runtime_error)
  {
    static const int BLOCK_SIZE = 768;
	
    std::ifstream file(filename.c_str(),std::ios::in|std::ios::binary);
    if (!file)
      throw std::runtime_error("Could not read the file!");
	
    int size = getFileSize(file);
    int usableBlockSize = BLOCK_SIZE - sizeof(FileHeader);
    int blockCount = (size / usableBlockSize) + 1;
    int blockNumber = -1;
	
    FileHeader header;
    header.file_size = size;
    header.block_count = blockCount;
    header.block_number = blockNumber;
	
    unsigned char* buf = new unsigned char[BLOCK_SIZE];
	
    m_netProtocol->sendCommand("file",utils::Buffer((unsigned char*) &header,sizeof(header)));
	
    while (size > 0)
      {
	int bytesToSend = min(usableBlockSize,size);
		
	header.block_number = ++blockNumber;
	memcpy(buf,&header,sizeof(header));
		
	file.read(reinterpret_cast<char*>(buf+sizeof(header)),bytesToSend);
	if (!file)
	  throw std::runtime_error("Unexpected eof");
		
	m_netProtocol->sendCommand("file",utils::Buffer(buf,sizeof(header)+bytesToSend));
		
	size -= bytesToSend;
      }
	
    assert(size == 0);
	
    file.close();
  }

  void FileProtocol::commandReceived(const std::string& command,
				     const utils::Buffer& buf)
  {
    static bool active = false;
    static int lastBlockNumber = -1;
    static int currentFileSize = -1;
    static int bytesRead = -1;
    static int currentBlockCount = -1;
    static const char* FILE_NAME = "/tmp/fileprotocol_temp_.dat";
    static std::ofstream file;

    const unsigned char* data = buf.getPtr();
    int len = buf.getLen();
	
    //command should be "file"
    assert(command == "file"); //TODO
	
    if (len < (int) sizeof(FileHeader))
      {
	//TODO
      }
	
    FileHeader *header = (FileHeader*) data;
	
    if (!active)
      {
	if (header->block_number != -1)
	  {
	    //TODO
	  }
		
	lastBlockNumber = -1;
	currentFileSize = header->file_size;
	bytesRead = 0;
	currentBlockCount = header->block_count;
		
	file.open(FILE_NAME,std::ios::trunc|std::ios::out|std::ios::binary);
	if (!file)
	  {
	    //TODO
	  }
	active = true;
      }
    else
      {
	if (header->block_number != lastBlockNumber +1
	    || header->file_size != currentFileSize
	    || header->block_count != currentBlockCount)
	  {
	    //TODO
	  }
		
	const unsigned char* dataPos = data + sizeof(*header);
	int bytesLeft = len - sizeof(*header);
		
	file.write(reinterpret_cast<const char*>(dataPos),bytesLeft);
	if (!file)
	  {
	    //TODO
	  }
		
	bytesRead += bytesLeft;
	++lastBlockNumber;
		
	if (lastBlockNumber == currentBlockCount-1) // am ende?
	  {
	    if (bytesRead != currentFileSize)
	      {
				//TODO
	      }
	    active = false;
	    file.close();
	    m_fileReceiver->commandReceived("frec",
					    utils::Buffer(reinterpret_cast<const unsigned char*>(FILE_NAME),
							  strlen(FILE_NAME)+1));
	  }
      }  
  }


} //end of namespace
