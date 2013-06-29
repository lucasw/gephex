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

#include "controlmodel.h"

#include <sstream>
#include <stdexcept>

#include "icontrolview.h"
#include "icontrolconnectview.h"

#include "interfaces/imodelcontrolreceiver.h"
#include "interfaces/ierrorreceiver.h"

#include "utils/buffer.h"
#include "utils/bufferstream.h"
#include "utils/string_.h"
#include "utils/structreader.h"

namespace gui
{

  //------------------------------------------------------------------------

  class ControlElement //: public IPersistent
  {
  private:
    std::string m_name;
    Point _pos;
    int _nodeID; //which GraphNode are we related to
    //int controlNodeID; //associated module in engine
    int _inputIndex;
    std::string _widgetType; // see controlwidgetfactory
    ControlModel::ParamMap _params;
    int magicNumber;
		
  public:
    typedef ControlModel::ParamMap ParamMap;

    ControlElement(const std::string& name,
		   const Point&,int _nodeID,
		   int _inputIndex,
		   const std::string& _widgetType,
		   const ParamMap& params);
		
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

    ParamMap params() const
    {
      return _params;
    }

    const void setParams(const ParamMap& params)
    {
      _params = params;
    }
    
  };


  ControlElement::ControlElement(const std::string& name,
				 const Point& pos,int nodeID,
				 int inputIndex,
				 const std::string& widgetType,
				 const ParamMap& params)
    : m_name(name),_pos(pos), _nodeID(nodeID), _inputIndex(inputIndex), 
    _widgetType(widgetType), _params(params)
  {
  }

  //------------------------------------------------------------------------

  class LabelElement //: public IPersistent
  {
  private:
    Point m_pos;
    std::string m_text;

		
  public:
    typedef ControlModel::ParamMap ParamMap;

    LabelElement(const Point& pos, const std::string& text)
      : m_pos(pos), m_text(text) {}
		
    std::string text() const
    {
      return m_text;
    }

    Point position() const
    {
      return m_pos;
    }
		
    void setPosition(const Point& p)
    {
      m_pos = p;
    }    
  };

  //------------------------------------------------------------------------
  
  ControlModel::ControlModel(IModelControlReceiver& r,
                             IErrorReceiver& log)
    : lastControlID(1023), lastLabelID(1023), mcr(&r), m_log(log)
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
	 << ' ' << cElem.position() << "|";
	  
      os.flush();

      utils::Buffer ob2(100);
      utils::OBufferStream os2(ob2);
      utils::StructReader sr(cElem.params());
      sr.serialize(os2);
      os2.flush();

      return ob + ob2;
    }

    ControlElement buffer2CElem(const utils::Buffer& b)
    {
      utils::IBufferStream is(b);
		
      utils::String name;
      int nodeID, inputIndex;
      Point p;
      utils::String widgetType;
		
      is >> name >> nodeID >> inputIndex >> widgetType >> p;

      std::string allText(reinterpret_cast<const char*>(b.getPtr()),
			  b.getLen());

      std::string::size_type pos = allText.find('|');
      
      utils::StructReader::ConfigMap params;
      if (pos != std::string::npos)
	{
	  allText = allText.substr(pos+1);
	  utils::StructReader sr(allText);
	  
	  params = sr.getMap();
	}

      return ControlElement(name, p, nodeID, inputIndex, widgetType, params);
    }

    //------------------------------------------------------------------------

    utils::Buffer lElem2Buffer(const LabelElement& lElem)
    {
      utils::Buffer ob(100);
      utils::OBufferStream os(ob);

      os << lElem.position() << ' ' << utils::String(lElem.text());
	  
      os.flush();

      return ob;
    }

    LabelElement buffer2LElem(const utils::Buffer& b)
    {
      utils::IBufferStream is(b);
		
      utils::String t;
      Point p;
		
      is >> p >> t;

      return LabelElement(p, t);
    }
  }
	
  void ControlModel::addControl(const Point& pos, const std::string& name,
				int nodeID,int inputIndex,
				const std::string& widgetType,
				const ParamMap& params)
  {
    int controlID = ++lastControlID;
		
    ControlElement temp(name, pos, nodeID, inputIndex, widgetType, params);
		
    mcr->setModuleData(nodeID,controlID,
		       cElem2Buffer(temp));
  }
	
	
  void ControlModel::delControl(int controlID)
  {
    ControlMap::iterator i = controls.find(controlID);
    if (i == controls.end())
      {
        m_log.warning("Unknown controlID at ControlModel::delControl()");
        return;
      }
		
    mcr->unSetModuleData(i->second->nodeID(),controlID);
  }
	
  void ControlModel::moveControl(int controlID, const Point& pos)
  {
    ControlMap::iterator i = controls.find(controlID);
    if (i == controls.end())
      {
        m_log.warning("Unknown controlID at ControlModel::moveControl()");
        return;
      }
		
    ControlElement copy = *i->second;
    copy.setPosition(pos);
		
    mcr->setModuleData(copy.nodeID(),i->first,cElem2Buffer(copy));
  }

  void ControlModel::renameControl(int controlID, const std::string& name)
  {
    ControlMap::iterator i = controls.find(controlID);
    if (i == controls.end())
      {
        m_log.warning("Unknown controlID at ControlModel::renameControl()");
        return;
      }
		
    ControlElement copy = *i->second;
    copy.rename(name);
		
    mcr->setModuleData(copy.nodeID(),i->first,cElem2Buffer(copy));
  }

  void ControlModel::addLabel(const Point& pos, const std::string& text)
  {
    int labelID = ++lastLabelID;
		
    LabelElement temp(pos, text);
		
    mcr->setEditGraphData(labelID,
                          lElem2Buffer(temp));
  }

  void ControlModel::moveLabel(int labelID, const Point& pos)
  {
    LabelMap::iterator i = labels.find(labelID);
    if (i == labels.end())
      {
        m_log.warning("Unknown labelID at ControlModel::moveLabel()");
        return;
      }
		
    LabelElement copy = *i->second;
    copy.setPosition(pos);
		
    mcr->setEditGraphData(i->first, lElem2Buffer(copy));
  }

  void ControlModel::delLabel(int labelID)
  {
    LabelMap::iterator i = labels.find(labelID);
    if (i == labels.end())
      {
        m_log.warning("Unknown labelID at ControlModel::delLabel()");
        return;
      }
		
    mcr->unSetEditGraphData(labelID);
  }
	
  void ControlModel::moduleDataSet(int /*moduleID*/, int type,
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
	view->controlAdded(controlID,cElem->name(),cElem->nodeID(),
			   cElem->inputIndex(), cElem->widgetType(),
			   cElem->params());

	view->controlMoved(controlID,cElem->position());

        try {
          if (connectView != 0)
            connectView->controlConnected(cElem->nodeID(),cElem->inputIndex());
        }
        catch(std::exception& e)
          {
            std::ostringstream txt;
            txt << "Could not connect control at ControlModel::"
                << "moduleDataSet(): '"
                << e.what() << "'";
            m_log.error(txt.str());
          }
      }
    else
      {
	utils::AutoPtr<ControlElement> oldElem = i->second;

	ControlElement cElem = buffer2CElem(buf);

	if (cElem.widgetType() != oldElem->widgetType()
	    || cElem.nodeID() != oldElem->nodeID()
	    || cElem.inputIndex() != oldElem->inputIndex())
	  {
            m_log.error("Internal data inconsistent at "
                        "ControlModel::moduleDataSet()");
            return;
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
            m_log.warning("No change at "
                          "ControlModel::moduleDataSet()");
            return;
	  }
      }
  }
	
  void ControlModel::moduleDataUnSet(int moduleID, int type)
  {
    int controlID = type;
		
    ControlMap::iterator i = controls.find(controlID);
    if (i == controls.end())
      {
        m_log.warning("Unknown moduleID at ControlModel::moduleDataUnSet()");
        return;
      }

    int nodeID = i->second->nodeID();
    int inputIndex = i->second->inputIndex();
    controls.erase(i);

    if (nodeID != moduleID)
      {
        m_log.error("Internal data inconsistent at ControlModel::"
                    "moduleDataUnSet()");
        return;
      }

    try {
    if (connectView != 0)
      connectView->controlDisconnected(nodeID, inputIndex);
    }
    catch (std::exception& e) {
      std::ostringstream txt;
      txt << "Could not disconnect control at ControlModel::"
          << "moduleDataUnSet(): '"
          << e.what() << "'";
      m_log.error(txt.str());
    }

    view->controlDeleted(type);
  }
	
  void ControlModel::syncDataStarted()
  {
    controls.clear();
  }
	
  void ControlModel::syncDataFinished()
  {
    //TODO
  }

  void ControlModel::graphDataSet(int type, const utils::Buffer& buf)
  {
    int labelID = type;
		
    LabelMap::iterator i = labels.find(labelID);
    if (i == labels.end())
      {
	if (labelID > lastLabelID)
	  {
	    lastLabelID = labelID;
	  }

	utils::AutoPtr<LabelElement> 
	  lElem ( new LabelElement(buffer2LElem(buf)) );

	labels.insert(std::make_pair(labelID, lElem));

        try {
          view->labelAdded(labelID, lElem->text());
          view->labelMoved(labelID, lElem->position());
        } catch(std::exception& e) {
          std::ostringstream txt;
          txt << "Could not add label at ControlModel::"
              << "graphDataSet(): '"
              << e.what() << "'";
          m_log.error(txt.str());
        }
      }
    else
      {
	utils::AutoPtr<LabelElement> oldElem = i->second;

	LabelElement lElem = buffer2LElem(buf);

	if (!(lElem.position() == oldElem->position()))
	  {
            try {
	    view->labelMoved(labelID, lElem.position());
            } catch (std::exception& e) {
              std::ostringstream txt;
              txt << "Could not move label at ControlModel::"
                  << "graphDataSet(): '"
                  << e.what() << "'";
              m_log.error(txt.str());
            }
	  }
	else
	  {
            m_log.warning("No change at "
                          "ControlModel::graphDataSet()");
	  }
      }
  }

  void ControlModel::graphDataUnSet(int type)
  {
    int labelID = type;
		
    LabelMap::iterator i = labels.find(labelID);
    if (i == labels.end())
      {
        m_log.warning("Unknown labelID at ControlModel::graphDataUnSet()");
        return;
      }

    labels.erase(i);

    try {
    view->labelDeleted(type);
    } catch (std::exception& e) {
      std::ostringstream txt;
      txt << "Could not delete label at ControlModel::"
          << "graphDataUnSet(): '"
          << e.what() << "'";
      m_log.error(txt.str());      
    }
  }

  void ControlModel::syncGraphDataStarted()
  {
    labels.clear();
  }

  void ControlModel::syncGraphDataFinished()
  {
    //TODO
  }

}
