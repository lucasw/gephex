#include "sequencertest.h"
#include "sequencer/sequencer.h"
#include "sequencer/sequence.h"
#include "interfaces/imodelgraphcontrolreceiver.h"
#include "interfaces/imodelgraphcontrolsender.h"
#include "interfaces/isequencecontrolsender.h"
#include "interfaces/isequencecontrolreceiver.h"
#include "interfaces/irenderercontrolreceiver.h"
#include "interfaces/isequenceupdatereceiver.h"

#include <string>
#include <iostream>
#include <ctime>

class DummySequenceUpdateReceiver: public ISequenceUpdateReceiver
{
private:
	double _time;

public:
	virtual void sceneModified(const std::string& name, int newPos, int newLen);

	virtual void sceneDeleted(const std::string& name);

	virtual void sceneAdded(const std::string& name, int newPos, int newLen);

	virtual void update(double time);

	virtual void sequenceStarted(double time);

	virtual void sequenceStopped();

	virtual void sequencePaused(double time);

	virtual void sequenceCreated(const std::string& name);

	virtual void sequenceChanged(const std::string& name);

	virtual void sequenceDeleted(const std::string& name);
};

void DummySequenceUpdateReceiver::sceneAdded(const std::string& name, int newPos, int newLen)
{
	std::cout<<"Added Scene: " << name << " " << newPos << " " << newLen << "\n";
}

void DummySequenceUpdateReceiver::sceneDeleted(const std::string& name)
{
	std::cout<<"Deleted Scene: " << name << "\n ";
}

void DummySequenceUpdateReceiver::sceneModified(const std::string& name, 
												int newPos, int newLen)
{
	std::cout<<"Modified Scene " << name << " to: " << newPos << " " <<newLen <<std::endl;
}

void DummySequenceUpdateReceiver::sequenceChanged(const std::string& name)
{}

void DummySequenceUpdateReceiver::sequenceCreated(const std::string& name)
{
	if(strcmp(name.c_str(), "Sequence1")!= 0)
	{
		throw std::runtime_error("Fuckfuck fuck fuck fuck fuck fuck fuck you...");
	}
}

void DummySequenceUpdateReceiver::sequenceDeleted(const std::string& name)
{}

void DummySequenceUpdateReceiver::sequencePaused(double time)
{}

void DummySequenceUpdateReceiver::sequenceStarted(double time)
{
	std::cout<<"Been started at " << time << "\n";
}

void DummySequenceUpdateReceiver::sequenceStopped()
{
	std::cout<<"Been stopped at " << _time << "\n";
}

void DummySequenceUpdateReceiver::update(double time)
{
	_time = time;
	std::cout<<"Received update at " << _time << "\n";
	
}


class DummyModelGraphControlReciever: public IModelGraphControlReceiver
{ 
public:
	virtual void changeGraph(const std::string& name);	
};

void DummyModelGraphControlReciever::changeGraph(const std::string& name)
{
	std::cout<<"Changed Graph to: "<<name<<std::endl;
}

class DummySequenceControlSender: public ISequenceControlSender
{
private:
	ISequenceControlReceiver *scr;
public:
	virtual void registerSequenceControlReceiver(ISequenceControlReceiver&);
	void createSequence(const std::string& name);
	void changeSequence(const std::string& name);
	void startSequence(double time, bool LOOPED);
	void pauseSequence(double time);
	void stopSequence();
	void addGraph(const std::string& name, int pos, int time);
	void modifyGraph(const std::string& name, int newPos, int newLen);
	void deleteGraph(const std::string& name);
};

void DummySequenceControlSender::addGraph(const std::string& name, int pos, int time)
{
	scr->graphAdded(name, pos, time);
}

void DummySequenceControlSender::changeSequence(const std::string &name)
{
	scr->sequenceChanged(name);
}

void DummySequenceControlSender::createSequence(const std::string& name)
{
	scr->sequenceCreated(name);
}

void DummySequenceControlSender::deleteGraph(const std::string& name)
{
	scr->graphDeleted(name);
}

void DummySequenceControlSender::modifyGraph(const std::string& name, int newPos, int newLen)
{
	scr->graphModified(name, newPos, newLen);
}

void DummySequenceControlSender::pauseSequence(double time)
{
	scr->sequencePaused(time);
}

void DummySequenceControlSender::startSequence(double time, bool loop)
{
	scr->sequenceStarted(time, loop);
}

void DummySequenceControlSender::stopSequence()
{
	scr->sequenceStopped();
}

void DummySequenceControlSender::registerSequenceControlReceiver(ISequenceControlReceiver& iscr)
{
	scr = &iscr;
}

class DummyRendererControlReceiver: public IRendererControlReceiver
{
public:
	virtual void start();
	virtual void stop();
 virtual void setInput(int nodeID,int inputIndex,const utils::Buffer& buf);

};

void DummyRendererControlReceiver::start()
{
	std::cout<<"been started\n";
}

void DummyRendererControlReceiver::stop()
{
	std::cout<<"beenStopped\n";
}

void DummyRendererControlReceiver::setInput(int nodeID, int inputeIndex, const utils::Buffer& buf)
{}

std::string SequencerTest::getName() const
{
	return "Sequencer Tester";
}

std::string SequencerTest::getDescription() const
{
	return "test halt....mann oh mann...";
}

void SequencerTest::pre() throw(std::runtime_error)
{}

void SequencerTest::run() throw(std::runtime_error)
{
	DummyRendererControlReceiver* drcr = new DummyRendererControlReceiver();
	DummyModelGraphControlReciever* dmgcr = new DummyModelGraphControlReciever();
	DummySequenceControlSender* dscs = new DummySequenceControlSender();
	DummySequenceUpdateReceiver* sur = new DummySequenceUpdateReceiver();

	sequencer::Sequencer* sqr = new sequencer::Sequencer();
	sqr->registerModelGraphControlReceiver(*dmgcr);
	sqr->registerRendererControlReceiver(*drcr);
	sqr->registerSequenceUpdateReceiver(*sur);

	dscs->registerSequenceControlReceiver(*sqr);

	dscs->createSequence("Sequence1");
	dscs->changeSequence("Sequence1");
	dscs->addGraph("Graph1", 0, 100);
	dscs->addGraph("Graph2", 1, 50);
	dscs->addGraph("Graph3", 2, 100);
	dscs->addGraph("Graph4", 1, 90);

	dscs->modifyGraph("Graph3", 2, 200);
	dscs->modifyGraph("Graph2", 2, 100);
	dscs->modifyGraph("Graph4", 3, 90);



	//dscs->deleteGraph("Graph1"); try 1st elem
	//dscs->deleteGraph("Graph4"); try last elem
	dscs->deleteGraph("Graph2");
	
	
	clock_t start_time = clock();
	clock_t curr_time = start_time;
	clock_t end_time = start_time + 400; //Hack
	dscs->startSequence(start_time, false);
	while(start_time<end_time){
		curr_time += (clock()-curr_time);
		if(curr_time >= start_time+5)
		{
			start_time+= 5;
			sqr->update(5);
		}
	}
	dscs->stopSequence();
	getchar();
}

void SequencerTest::post() throw(std::runtime_error)
{}