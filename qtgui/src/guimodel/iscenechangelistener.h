#ifndef INCLUDED_ISCENE_CHANGE_LISTENER_H
#define INCLUDED_ISCENE_CHANGE_LISTENER_H

namespace gui
{

  /**
   * This is the interface for a class that listens to changes of
   * a scenesequencer (see ISceneSequencer). It is called whenever
   * a scene is inserted, deleted, changed or moved. It is a view
   * of the SceneSequencer (which is the model).
   */

  class ISceneChangeListener
  {
  public:
    virtual ~ISceneChangeListener() {}

    /**
     * A new scene has been inserted before the position pos.
     * @param id the identifier of the scene
     * @param pos the position before which the scene has been inserted
     *        0 <= pos <= numberOfScenes. If pos == numberOfScenes then
     *        the scene has been appended to the end.
     * @param content the content of the scene (f.e. the graph:scnapshot id)
     * @param length the length of the scene in ms
     */
    virtual void sceneInserted(int id, int pos,
			       const std::string& content,
			       int length) = 0;

    /**
     * A scene has been deleted.
     * @param id the identifier of the scene
     */
    virtual void sceneDeleted(int id) = 0;

    /**
     * The length of a scene has changed.
     * @param id the identifier of the scene
     * @param newLen the new length of the scene in ms
     */
    virtual void sceneLengthChanged(int id, int newLen) = 0;

    /**
     * The Position of a scene has changed.
     * @param id the identifier of the scene
     * @param newPos the new position of the scene. 
     *               0 <= pos < numberOfScenes.
     */
    virtual void sceneMoved(int id, int newPos) = 0;
  };

}

#endif

