#include "sequencewidget.h"
#include "scenewidget.h"

#include <stdexcept>

#include <qheader.h>
#include <qlayout.h>
#include <qpopupmenu.h>

#include "utils/stringtokenizer.h"

namespace gui
{
	
	static int MILLLISECONDS_PER_PIXEL = 20;
	
	namespace
	{
		typedef std::map<int,int> SceneMap;
		typedef std::list<utils::AutoPtr<SceneWidget> > SceneList;
		
		int time2pixels(int time)
		{
			return time / MILLLISECONDS_PER_PIXEL;
		}
		
		int pixels2time(int pixels)
		{
			return pixels *  MILLLISECONDS_PER_PIXEL;
		}
		
		void destroyHeader(QHeader* header)
		{
			delete header;
		}
		
		bool insertSceneIntoHeader(const SceneWidget& scene, QHeader* header,
			SceneMap& section2scene, int size )
		{				
			std::string text = scene.command();
			
			if (text.find("changeGraph:",0) == 0)
				text = text.substr(12);

			int index = header->addLabel(text.c_str(), size);
			
			//assert(index == section);
			bool b = 
				section2scene.insert(SceneMap::value_type(index,
				scene.sceneID())).second;
			
			assert(b); //TODO
			return true;
			
		}
		
		void fillHeader(QHeader* header, const SceneList& scenes,
						SceneMap& section2scene)
		{	  
			section2scene.clear();			
			
			for (SceneList::const_iterator it = scenes.begin();
			it != scenes.end(); ++it)
			{
				int size = time2pixels((*it)->length());
				insertSceneIntoHeader(**it, header, section2scene, size);
				
			}
		}

		SceneList::iterator getSceneByPos(SceneList& scenes, int pos)
		{
			int index = 0;
			SceneList::iterator it = scenes.begin();
			while (it != scenes.end() && index != pos)
			{
				++it;
				++index;
			}

			return it;
		}


		SceneList::const_iterator 
			getSceneByID(const SceneList& scenes, int sceneID, int* pos = 0)
		{
			int index = 0;
			for (SceneList::const_iterator it = scenes.begin();
				 it != scenes.end(); ++it, ++index)
			{
				if ( (*it)->sceneID() == sceneID )
				{
					if (pos != 0)
						*pos = index;
					return it;
				}
			}
			
			if (pos != 0)
				*pos = -1;
			return scenes.end();
		}
		
		SceneList::iterator 
			getSceneByID(SceneList& scenes, int sceneID, int* pos = 0)
		{
			int index = 0;
			for (SceneList::iterator it = scenes.begin();
			it != scenes.end(); ++it, ++index)
			{
				if ( (*it)->sceneID() == sceneID )
					{
					if (pos != 0)
						*pos = index;
					return it;
					}
			}
			
			if (pos != 0)
				*pos = -1;
			return scenes.end();
		}
	}
	
	SequenceWidget::SequenceWidget(QWidget* parent, const char* name, WFlags fl)
		: QWidget(parent, name, fl), oldX(0),
		header(0), currentSceneID(-1)
		/*,headerLayout(new QHBoxLayout(this))*/
	{
		this->resize(10000, 75);
		this->setMinimumSize(10000, 75);
		
		header = buildHeader();
	}
	
	SequenceWidget::~SequenceWidget()
	{		
	}					
	
	void SequenceWidget::paintEvent(QPaintEvent*)
	{
		QPen pen(SolidLine);
		pen.setColor(QColor(0,0,0));
		painter.begin(this);
		painter.setPen(pen);
		
		int oneSecond = 1000 / MILLLISECONDS_PER_PIXEL;
		int twohundredMillis = 200 / MILLLISECONDS_PER_PIXEL;
		
		for(int i = 0; i < 10000; ++i)
		{
			int h = height();
			int hShort = h - (0.075 * h);
			int hLong = h - (0.2 * h);			
			if ( i % oneSecond == 0 )
			{
				painter.drawLine(i, hLong, i, h);
			}
			else if ( i % twohundredMillis == 0 )
			{	
				painter.drawLine(i, hShort, i, h);
			}		
		}
		
		painter.end();
	}
	
	void SequenceWidget::started()
	{
	}
	
	void SequenceWidget::paused()
	{
	}
	
	void SequenceWidget::stopped()
	{
	}
	
	QHeader* SequenceWidget::buildHeader()
	{
		QHeader* h = new QHeader(this);
		
		h->setMovingEnabled(false);
		
		connect(h, SIGNAL( sizeChange(int, int, int) ),
			this, SLOT( sceneSizeChanged(int, int, int) ));
		
		connect(h, SIGNAL( clicked(int) ),
			this, SLOT( sceneClicked(int) ));
		
		return h;
	}
	
	void SequenceWidget::updateHeader()
	{
		destroyHeader(header);
		
		header = buildHeader();
		fillHeader(header,m_scenes, section2scene);
		header->resize(width(), height()*0.8);
		header->show();
	}  
	
	void SequenceWidget::sceneInserted(int id, int pos,
		const std::string& content, int length)
	{
		if (pos > m_scenes.size())
		{
			throw std::runtime_error("pos behind end at "
				"SequenceWidget::sceneInserted()");
		}
		else if (pos == m_scenes.size())
		{
			m_scenes.push_back(SceneWidgetPtr(new SceneWidget(id,content,
				length)));
		}
		else
		{
			
			SceneList::iterator it = getSceneByPos(m_scenes,pos);
			
			assert (it != m_scenes.end());
			
			m_scenes.insert(it,SceneWidgetPtr(new SceneWidget(id,content,length)));
		}

		updateHeader();
	}
	
    void SequenceWidget::sceneDeleted(int id)
	{
		SceneList::iterator it = getSceneByID(m_scenes,id);

		if (it == m_scenes.end())
		{
			throw std::runtime_error("No such scene at "
						"SequenceWidget::sceneDeleted()");
		}

		m_scenes.erase(it);
		updateHeader();
	}
	
    void SequenceWidget::sceneLengthChanged(int id, int newLen)
	{
		SceneList::const_iterator it = getSceneByID(m_scenes,id);

		if (it == m_scenes.end())
		{
			throw std::runtime_error("No such scene at "
						"SequenceWidget::sceneLengthChanged()");
		}

		(*it)->setLength(newLen);		

		updateHeader();
	}
	
    void SequenceWidget::sceneMoved(int id, int newPos)
	{	
		if (newPos >= m_scenes.size())
		{
			throw std::runtime_error("NewPos out of range at "
								"SequenceWidget::sceneMoved()");
		}
		SceneList::iterator it = getSceneByID(m_scenes,id);
		if (it == m_scenes.end())
		{
			throw std::runtime_error("No such scene at "
									"SequenceWidget::sceneMoved()");
		}

		SceneWidgetPtr temp (*it);
		m_scenes.erase(it);

		if (newPos == m_scenes.size())
		{
			m_scenes.push_back(temp);
		}
		else
		{
			SceneList::iterator it2 = getSceneByPos(m_scenes,newPos);
			assert (it2 != m_scenes.end());
			
			m_scenes.insert(it2,temp);
		}		

		updateHeader();
	}
	
	void SequenceWidget::time(int currentTime)
	{
		int newX = time2pixels(currentTime);		
		
		mainPainter.begin(this);
		
		QPen pen(SolidLine);
		pen.setColor(QColor(0,255,255));
		mainPainter.setPen(pen);
		
		RasterOp rop = mainPainter.rasterOp();
		mainPainter.setRasterOp(XorROP);
		mainPainter.drawLine(QPoint(oldX,0), QPoint(oldX,100));
		mainPainter.drawLine(QPoint(newX,0), QPoint(newX,100));
		mainPainter.setRasterOp(rop);
		mainPainter.end();	
		
		oldX = newX;
	}
	
	int SequenceWidget::getLength() const
	{
		int length = 0;

		for (SceneList::const_iterator it = m_scenes.begin();
			 it != m_scenes.end(); ++it)
		{
			length += (*it)->length();
		}
		
		return length;
	}
	
	void SequenceWidget::sceneSizeChanged(int section, int oldSize,
		int newSize)
	{
		SceneMap::const_iterator it = section2scene.find(section);
		if (it == section2scene.end())
		{
			throw std::runtime_error("Unknown section at "
				"SequenceWidget::sceneSizeChanged()");
		}
		
		int sceneID = it->second;
		
		/*SceneList::const_iterator sceneIt = getSceneByID(m_scenes,sceneID);
		if (sceneIt == m_scenes.end())
		{
			throw std::runtime_error("Unknown sceneID at "
				"SequenceWidget::sceneSizeChanged()");
		}*/		
		
		int newLength = pixels2time(newSize);
		//int oldLength = pixels2time(oldSize);

		emit userChangedSceneLength(sceneID,newLength);		
	}
	
	void SequenceWidget::sceneIndexChanged(int section, int fromIndex,
		int toIndex)
	{
		SceneMap::const_iterator it = section2scene.find(section);
		
		if ( it == section2scene.end() )
		{
			throw std::runtime_error("section not found at "
				"SequenceWidget::sceneIndexChanged()");
		}
		
		int actionID = it->second;
		
		SceneList::const_iterator it2 = getSceneByID(m_scenes,actionID);
		
		if ( it2 == m_scenes.end() )
		{
			throw std::runtime_error("actionID not found at "
				"SequenceWidget::sceneIndexChanged()");
		}
		
		//TODO
	}
	
	void SequenceWidget::sceneClicked(int section)
	{
		QPopupMenu *popme = new QPopupMenu(this, "pop"); //TODO: wird das deleted?
		
		SceneMap::const_iterator it = section2scene.find(section);
		if (it == section2scene.end())
		{
			throw std::runtime_error("Section not found at "
				"SequenceWidget::sceneClicked()");
		}
		currentSceneID = it->second;
		
		popme->insertItem("Properties",SequenceWidget::SCENE_PROPERTIES);
		popme->insertItem("Remove",SequenceWidget::SCENE_KILL);
		
		popme->move(mapToGlobal(QPoint(header->sectionPos(section), 0)));
		popme->show();
		
		connect (popme, SIGNAL( activated(int) ), 
			this, SLOT (scenePopupActivated(int)));
	}
	
	void SequenceWidget::scenePopupActivated(int action)
	{
		switch(action)
		{
		case SCENE_PROPERTIES:
			//TODO
			break;
		case SCENE_KILL:
			assert( currentSceneID != -1 );
			emit userDeletedScene( currentSceneID );
			break;
		}
	}
	
}

