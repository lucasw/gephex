#ifndef INCLUDED_SEQUENCE_FILE_SYSTEM_H
#define INCLUDED_SEQUENCE_FILE_SYSTEM_H

#include <string>
#include <map>
#include <list>

namespace sequencer
{
	
  class Sequence;
	
  class SequenceFileSystem
    {
    public:
      typedef std::map<std::string, std::string> FileMap;
      SequenceFileSystem(const std::string& basePath);

      std::list<std::pair<std::string, std::string> > getIDsAndNames();
		
      void loadSequence(const std::string sequenceName, Sequence& destination);
		
      void saveSequence(const std::string& name, const Sequence& toSave);

      void deleteSequence(const std::string& name);
		
      //bool SequenceExists(const std::string& SequenceName) const;
		
      /*		void rename(const std::string& SequenceName,
			const std::string& newSequenceName);*/
		
    private:
      std::string m_basePath;
      FileMap fileNames;
    };
	
} // end of namespace

#endif
