#ifndef _INCLUDED_SCENE_WIDGET_H_
#define _INCLUDED_SCENE_WIDGET_H_

#include <string>

namespace gui
{

  class SceneWidget
  {    
  private:
	int m_sceneID;
    std::string m_command;    
    int m_length;
  public:
    SceneWidget( int sceneID, const std::string& command, int length);

    std::string command() const;	
    int length() const;
	int sceneID() const;
	    
    void setLength(int);
    
  };

}
#endif
