#ifndef INCLUDED_ISCENE_SEQUENCER_H
#define INCLUDED_ISCENE_SEQUENCER_H

#include <string>

namespace gui
{

  /**
   * This is the interface for a Sequencer that is based on Scenes.
   * The sequencer contains a list of scenes that can be deleted
   * or changed. New Scenes can only be appended at the end for the moment.
   */
  class ISceneSequencer
  {
  public:

    virtual ~ISceneSequencer() {}


    /**
     * Append a new scene at the end of the current scenes.
     * @param content the content (= command that is executed at the 
     *                beginning of) the scene
     * @param length the length of the scene in ms
     */
    virtual void appendScene(const std::string& content, int length) = 0;

    /**
     * Deletes a scene.
     * If id isnt valid, nothing happens.
     * @param id the id of the scene to be deleted
     */
    virtual void deleteScene(int id) = 0;

    /**
     * Changes the length of a scene.
     * If id isnt valid, nothing happens.
     * @param id the id of the scene to be changed
     * @param newLength the new length in ms
     */
    virtual void changeSceneLength(int id, int newLength) = 0;


    /**
     * Determins wether the sequencer loops at the end.
     * @param loop true -> sequencer loops, false -> sequencer does not
     */
    virtual void loop(bool loop) = 0;

  };

}

#endif
