#include "controlmodel.h"

//#include <sstream>
#include <stdexcept>

#include "icontrolview.h"
#include "icontrolconnectview.h"

#include "interfaces/imodelcontrolreceiver.h"
#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"


namespace gui
{
	
  class ControlElement //: public IPersistent
  {
  private:
    std::string m_name;
    Point _pos;
    int _nodeID; //which GraphNode are we related to
    //int controlNodeID; //associated module in engine
    int _inputIndex;
    std::string _widgetType; // see controlwidgetfactory
    int magicNumber;
		
  public:
    ControlElement(const std::string& name,
		   const Point&,int _nodeID,
		   int _inputIndex,
		   const std::string& _widgetType);
		
    std::string name() const
    {
      return m_name;
    }

    void rename(const std::string& newName)
    {
      m_name = newName;
    }

    int nodeID() const
    {
      return _nodeID;	
    }
		
    std::string widgetType() const
    {
      return _widgetType;
    }
		
    int inputIndex() const
    {
      return _inputIndex;
    }
		
    const Point& position() const
    {
      return _pos;
    }
		
    void setPosition(const Point& p)
    {
      _pos = p;
    }
  };
	
  ControlElement::ControlElement(const std::string& name, const Point& pos,int nodeID,
				 int inputIndex, const std::string& widgetType)
    : m_name(name),_pos(pos), _nodeID(nodeID), _inputIndex(inputIndex), 
    _widgetType(widgetType)
  {
  }
	
	
  ControlModel::ControlModel(IModelControlReceiver& r)
    : lastControlID(1023), mcr(&r)
  {
  }
	
  ControlModel::~ControlModel()
  {		
  }
	
  void ControlModel::registerControlView(IControlView& v)
  {
    view = &v;
  }
	
  void ControlModel::registerControlConnectView(IControlConnectView& v)
  {
    connectView = &v;
  }

  namespace
  {
    utils::Buffer cElem2Buffer(const ControlElement& cElem)
    {
      utils::Buffer ob(100);
      utils::OBufferStream os(ob);

      os << utils::String(cElem.name()) << ' ' << cElem.nodeID() << ' ' 
	 << cElem.inputIndex() << ' '  << utils::String(cElem.widgetType())
	 << ' ' << cElem.position();
	  
      os.flush();
      return ob;
    }

    ControlElement buffer2CElem(const utils::Buffer& b)
    {
      utils::IBufferStream is(b);
		
      utils::String name;
      int nodeID, inputIndex;
      Point p;
      utils::String widgetType;
		
      is >> name >> nodeID >> inputIndex >> widgetType >> p;
		
      return ControlElement(name, p,nodeID,inputIndex,widgetType);
    }
  }
	
  void ControlModel::addControl(const Point& pos, const std::string& name,
				int nodeID,int inputIndex,
				const std::string& widgetType)
  {
    int controlID = ++lastControlID;
		
    ControlElement temp(name, pos, nodeID, inputIndex, widgetType);
		
    mcr->setModuleData(nodeID,controlID,
		       cElem2Buffer(temp));
  }
	
	
  void ControlModel::delControl(int controlID)
  {
    ControlMap::iterator i = controls.find(controlID);
    if(i == controls.end())
      throw std::runtime_error("FUCK YOUUUUUUU!!!!!!....");
		
    mcr->unSetModuleData(i->second->nodeID(),controlID);		
  }
	
  void ControlModel::moveControl(int controlID, const Point& pos)
  {
    ControlMap::iterator i = controls.find(controlID);
    if(i == controls.end())
      throw std::runtime_error("FUCK YOUUUUUUU!!!!!!....");
		
    ControlElement copy = *i->second;
    copy.setPosition(pos);
		
    mcr->setModuleData(copy.nodeID(),i->first,cElem2Buffer(copy));
  }

  void ControlModel::renameControl(int controlID, const std::string& name)
  {
    ControlMap::iterator i = controls.find(controlID);
    if(i == controls.end())
      throw std::runtime_error("FUCK YOUUUUUUU!!!!!!....");
		
    ControlElement copy = *i->second;
    copy.rename(name);
		
    mcr->setModuleData(copy.nodeID(),i->first,cElem2Buffer(copy));
  }
	
  void ControlModel::moduleDataSet(int moduleID, int type,
				   const utils::Buffer& buf)
  {
    int controlID = type;
		
    ControlMap::iterator i = controls.find(controlID);
    if (i == controls.end())
      {
	if (controlID > lastControlID)
	  {
	    lastControlID = controlID;
	  }
			
			
	utils::AutoPtr<ControlElement> 
	  cElem ( new ControlElement(buffer2CElem(buf)) );

	controls[controlID] = cElem;
	view->controlAdded(controlID,cElem->name(),cElem->nodeID(),cElem->inputIndex(),
			   cElem->widgetType());
			
	view->controlMoved(controlID,cElem->position());
			
	if (connectView != 0)
	  connectView->controlConnected(cElem->nodeID(),cElem->inputIndex());
      }
    else
      {
	utils::AutoPtr<ControlElement> oldElem = i->second;
			
	ControlElement cElem = buffer2CElem(buf);
			
	if (cElem.widgetType() != oldElem->widgetType()
	    || cElem.nodeID() != oldElem->nodeID()
	    || cElem.inputIndex() != oldElem->inputIndex())
	  {
	    throw std::runtime_error("Im Controlmodel ist die Hölle los!");
	  }

	if (!(cElem.name() == oldElem->name()))
	  {
	    view->controlRenamed(controlID, cElem.name());
	  }
			
	if (!(cElem.position() == oldElem->position()))
	  {
	    view->controlMoved(controlID,cElem.position());
				
	  }
	else
	  {
	    throw std::runtime_error("WAS IST NUR LOS HIER????");
	  }
      }
  }
	
  void ControlModel::moduleDataUnSet(int moduleID, int type)
  {
    int controlID = type;
		
    ControlMap::iterator i = controls.find(controlID);
    if(i == controls.end())
      throw std::runtime_error("FUCK YOUUUUUUU!!!!!!....");
		

    int nodeID = i->second->nodeID();
    int inputIndex = i->second->inputIndex();
    controls.erase(i);

    if (connectView != 0)
      connectView->controlDisconnected(nodeID, inputIndex);
		

    view->controlDeleted(type);
		

    if (nodeID != moduleID)
      {
	throw std::runtime_error("moduleDataUnSet: shit detection activated!");
      }
  }
	
  void ControlModel::syncDataStarted()
  {
    //TODO
  }
	
  void ControlModel::syncDataFinished()
  {
    //TODO
  }
	
}
