#ifndef INCLUDED_ITAGGER_H
#define INCLUDED_ITAGGER_H

#include "isender.h"
#include "idatalistener.h"

namespace net {

  template <typename Tag>
  class ITagInterpreter;

  /**
   * ITagger is the abstract base class for classes that attach and
   * remove tags to data and forward it at the same time.
   * 
   * 
   */

  template <typename Tag>
  class ITagger : public ISender, public IDataListener
  {
  public:
    virtual ~ITagger() {}

    /**
     * Registers an interpreter for tagged data.
     *
     * @param interpreter the tag-interpreter that is called when
     *    tagged data is received
     */
    virtual void registerInterpreter(ITagInterpreter<Tag>& interpreter) = 0; 

    /**
     * Registers a sender object, that is internally used to forward
     * the data.
     * 
     * @param sender the sender object that is used for forwarding data
     */
    virtual void registerSender(ISender& sender) = 0;
    
    /**
     * Sets the tag that is attached to the data in future calls
     * to send.
     *
     * @param tag The tag that will be attached.
     */
    virtual void setTag(const Tag& tag) = 0;
  };
  
}

#endif
