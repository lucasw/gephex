#ifndef INCLUDED_ITAG_INTERPRETER_H
#define INCLUDED_ITAG_INTERPRETER_H

namespace utils{
  class Buffer;
}

namespace net
{

  /**
   * Is called by Tagger, whenever data arrives. 
   */
  template <typename Tag>
  class ITagInterpreter
  {
  public:
    
    /**
     * This method is called when tagged data has arrived.
     */
    virtual void dataReceived(const Tag& tag, const utils::Buffer&) = 0;
  };

} //end of namespace

#endif
