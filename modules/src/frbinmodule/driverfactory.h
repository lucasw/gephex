#ifndef INCLUDED_DRIVER_FACTORY_H
#define INCLUDED_DRIVER_FACTORY_H

#include <map>
#include <string>
#include <list>

//---------------------------------------------------------------------------

class IDriverConstructor
{
public:
	virtual std::list<std::string> supported_extensions() const = 0;
	virtual VideoFileDriver* create() const = 0;
};

template <class DRV>
class DriverConstructor : public IDriverConstructor
{
public:
	DriverConstructor() {}

	std::list<std::string> supported_extensions() const
	{ 
		return DRV::supported_extensions();
	}

	VideoFileDriver* create() const
	{ 
		return new DRV(); 
	}
};

//---------------------------------------------------------------------------

class DriverFactory
{
public:
	typedef std::list<IDriverConstructor*> CtorList;
	DriverFactory() {};
	~DriverFactory()
	{
		for (CtorList::iterator it = m_ctor_list.begin();
		     it != m_ctor_list.end(); ++it)
		{
			delete *it;
		}
		      
	}

	/**
	 * Ownership of ctor is transferred to the factory.
	 */
	void register_driver(IDriverConstructor* ctor)
	{		
		typedef std::list<std::string> ExtList;
		ExtList el = ctor->supported_extensions();
		for (ExtList::const_iterator it = el.begin(); it != el.end(); ++it)
		{
			CtorMap::iterator cit = m_ctors.find(*it);
			if (cit != m_ctors.end())
			{			
				//std::cout << "Driver for '" << *it << "' already claimed\n";
				cit->second.push_back(ctor);
			}
			else
			{
				CtorList l;
				l.push_back(ctor);
				m_ctors.insert(std::make_pair(*it, l));
			}
		}


		m_ctor_list.push_back(ctor);		
	}

	/**
	 * Returns 0 if there is no driver for this extension.
	 */
	std::list<IDriverConstructor*> get_drivers(const std::string& extension) const
	{
		CtorMap::const_iterator it = m_ctors.find(extension);
		if (it == m_ctors.end())
			return CtorList();
		else		
			return it->second;
		
	}

private:	
	typedef	std::map<std::string, CtorList> CtorMap;
	CtorMap m_ctors;

	CtorList m_ctor_list;
};

//---------------------------------------------------------------------------

#endif
