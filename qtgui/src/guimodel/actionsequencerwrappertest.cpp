#include "actionsequencerwrappertest.h"

#include <list>

#include "actionsequencerwrapper.h"
#include "iscenechangelistener.h"
#include "interfaces/isequencercontrolreceiver.h"

//#include <sstream>
#include <iostream>

#include <algorithm>

#include <sstream>

/*---------------------------------------------------------------------------*/

struct SceneInfo
{
	SceneInfo(int id_, const std::string& content_, int length_)
		: id(id_), content(content_), length(length_) {}
	
	typedef int id_type;
	
	id_type id;
	std::string content;
	int length;
};

std::ostream& operator<<(std::ostream& s,const SceneInfo& si)
{
	s << "id=" << si.id << "; content=<" << si.content << ">; length=" 
		<< si.length << ";";
	return s;
}

template <class T>
class MatchesID
{
public:
	typedef typename T::id_type id_type;
	MatchesID(id_type id) : m_id(id) {}
	
	bool operator()(const T& t) { return t.id == m_id; }
	
private:
	id_type m_id;
};

class MySceneChangeListener : public gui::ISceneChangeListener
{
private:
	void insert(const SceneInfo& info, int pos)
	{
		int index = 0;
		for (SceneList::iterator it = m_scenes.begin();
		it != m_scenes.end(); ++it, ++index)
		{
			if (index == pos)
			{
				m_scenes.insert(it,info);
				break;
			}
		}
		
		if (index == pos) // at the end?
			m_scenes.push_back(info);
		else if (index > pos)
		{
			std::ostringstream s;
			s << "pos == " << pos << std::endl;
			s << "index == " << index << std::endl;
			s.flush();
			
			throw std::runtime_error(s.str().c_str());
		}
	}
public:
	
	
	void sceneInserted(int id, int pos,
		const std::string& content,
		int length) 
	{
		SceneInfo info(id,content,length);
		insert(info,pos);
	}
	
	void sceneDeleted(int id) {
		SceneList::iterator it = std::find_if(m_scenes.begin(), m_scenes.end(),
			MatchesID<SceneInfo>(id));
		
		if (it == m_scenes.end())
			assert(!"no such scene!");//throw std::runtime_error("no such scene!");
		
		m_scenes.erase(it);
	}
	
	
	void sceneLengthChanged(int id, int newLen) {
		SceneList::iterator it = std::find_if(m_scenes.begin(), m_scenes.end(),
			MatchesID<SceneInfo>(id));
		
		if (it == m_scenes.end())
			assert(!"no such scene!");//throw std::runtime_error("no such scene!");
		
		it->length = newLen;
	}
	
	void sceneMoved(int id, int newPos) {
		SceneList::iterator it = std::find_if(m_scenes.begin(), m_scenes.end(),
			MatchesID<SceneInfo>(id));
		
		if (it == m_scenes.end())
			assert(!"no such scene!");//throw std::runtime_error("no such scene!");
		
		SceneInfo temp = *it;
		m_scenes.erase(it);
		
		insert(temp,newPos);
	}
	
	void print(std::ostream& s) const
	{
		s << "[";
		for (SceneList::const_iterator it = m_scenes.begin(); it != m_scenes.end();
		++it)
		{
			s << *it << " ";	
		}
		s << "]";
	}
private:
	typedef std::list<SceneInfo> SceneList;
	SceneList m_scenes;
};

std::ostream& operator<<(std::ostream& s, const MySceneChangeListener& m)
{
	m.print(s);
	return s;
}

class MyControlReceiver : public ISequencerControlReceiver
{
public:
	
	MyControlReceiver() : m_rec(0), lastID(-1) {}
	void registerSequenceUpdateReceiver(ISequenceUpdateReceiver& rec) {
		m_rec = &rec;
	}
	
	virtual void createSequence( const std::string& /*sequenceName*/ ) {}
	
	virtual void saveSequence( const std::string& /*id*/ ) {}
	
	virtual void changeSequence( const std::string& /*id*/ ) {}
	
	virtual void deleteSequence( const std::string& /*id*/ ) {}
	
	virtual void renameSequence( const std::string& /*id*/,
		const std::string& /*newName*/ ) {}
	
	virtual void start(  ) {}
	
	virtual void pause(  ) {}
	
	virtual void stop(  ) {}
	
	virtual void addAction( const std::string& command, int time ) {
		m_rec->actionAdded(++lastID,command, time);
	}
	
	virtual void changeActionTime( int id, int newTime ) {
		m_rec->actionTimeChanged(id,newTime);
	}
	
	virtual void deleteAction( int id ) {
		m_rec->actionDeleted( id );
	}
	
private:
	ISequenceUpdateReceiver* m_rec;
	int lastID;
	
};


ActionSequencerWrapperTest::ActionSequencerWrapperTest()
: EasyTest("ActionSequencerWrapperTest","")
{
}

ActionSequencerWrapperTest::~ActionSequencerWrapperTest()
{
}

void ActionSequencerWrapperTest::pre() throw(std::runtime_error)
{
}

void testListener(MySceneChangeListener& listener, const std::string& soll,
		  const std::string& fehlerText, bool verbose = false)
{
  std::ostringstream out;
  if (verbose)
    std::cout << listener << std::endl;

  out << listener;
  out.flush();
  if (out.str() != soll)
    throw std::runtime_error(fehlerText.c_str());
}
  

void ActionSequencerWrapperTest::run() throw(std::runtime_error)
{
	gui::ActionSequencerWrapper sequencer;
	
	MyControlReceiver actionSequencer;
	
	MySceneChangeListener listener;
	
	actionSequencer.registerSequenceUpdateReceiver(sequencer);
	
	sequencer.registerSceneChangeListener(listener);
	sequencer.registerSequencerControlReceiver(actionSequencer);
	
	
	testListener(listener,"[]","0.1");
	
	// Test 1
	sequencer.appendScene("hallo",4);
	testListener(listener,"[id=1; content=<hallo>; length=4; ]",
		     "1.1");
	
	sequencer.deleteScene(1);
	testListener(listener,"[]","1.2");
	
	sequencer.appendScene("ciao",3);
	testListener(listener,"[id=2; content=<ciao>; length=3; ]","1.3");

 	sequencer.appendScene("dumm",5);
	testListener(listener,
		     "[id=2; content=<ciao>; length=3; id=3; "
		     "content=<dumm>; length=5; ]","1.4");

	  
	  // Test 2
	  /*
	sequencer.appendScene("hallo",4);
	testListener(listener,"[id=1; content=<hallo>; length=4; ]","2.1");
	
	sequencer.appendScene("ciao",3);
	testListener(listener,"[id=1; content=<hallo>; length=4; id=2; content=<ciao>; length=3; ]","2.2");
		
	sequencer.appendScene("dumm",5);
	testListener(listener,"[id=1; content=<hallo>; length=4; id=2; content=<ciao>; length=3; id=3; content=<dumm>; length=5; ]","2.3");
	
	sequencer.deleteScene(2);
	testListener(listener,"[id=1; content=<hallo>; length=4; id=3; content=<dumm>; length=5; ]","2.4");
	*/

	  // Test 3
	  /*
	  sequencer.appendScene("base",3);
	  testListener(listener,"[id=1; content=<base>; length=3; ]","3.1",
		       true);

	  sequencer.appendScene("temp",5);
	  testListener(listener,"[id=1; content=<base>; length=3; id=2; content=<temp>; length=5; ]","3.2",false);

	  sequencer.deleteScene(2);
	  testListener(listener,"[id=1; content=<base>; length=3; ]","3.3",false);

	  sequencer.appendScene("neu",1);
	  testListener(listener,"[id=1; content=<base>; length=3; id=3; content=<neu>; length=1; ]","3.4",false);*/
}

void ActionSequencerWrapperTest::post() throw(std::runtime_error)
{
}
/*---------------------------------------------------------------------------*/
