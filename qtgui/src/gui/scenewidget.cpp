#include "scenewidget.h"

#include <list>
#include <string>

namespace gui
{

  SceneWidget::SceneWidget( int sceneID, const std::string& command,
							int length )
    : m_sceneID(sceneID), m_command(command), m_length(length)    
  {    
  }

  int SceneWidget::sceneID() const
  {
	  return m_sceneID;
  }

  std::string SceneWidget::command() const
  {
    return m_command;
  }
  
  int SceneWidget::length() const
  {
    return m_length;
  }

  void SceneWidget::setLength(int newLen)
  {
	  m_length = newLen;
  }

}
