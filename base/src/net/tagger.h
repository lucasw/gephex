#ifndef INCLUDED_TAGGER_H
#define INCLUDED_TAGGER_H

#include "itagger.h"

namespace net {

  /**
   * This class implements the ITagger interface.
   * It uses a policy class TagUtil to actually attach and
   * remove tags to data.
   *
   * The policy class must provide two static methods:
   *
   * static void attachTag(utils::Buffer& dst,
   *			  const std::string& tag,
   *			  const utils::Buffer& b);
   *
   * static void removeTag(utils::Buffer& dst,
   *			  std::string& tag,
   *			  const utils::Buffer& src);
   *
   * For an example see tagutils.h.
   * @see StringTagUtil
   * @see UInt32TagUtil
   */
  template <typename Tag, typename TagUtil>
  class Tagger : public ITagger<Tag>
  {

    Tagger(const Tagger<Tag, TagUtil>&); // not impl.
    Tagger& operator=(const Tagger<Tag, TagUtil>&); // not impl.
  public:
    Tagger();
    Tagger(ITagInterpreter<Tag>& i);

    virtual void registerInterpreter(ITagInterpreter<Tag>& i);

    virtual void registerSender(ISender& s);
    
    virtual void setTag(const Tag& t);

    virtual int send(const utils::Buffer& b);

    virtual void dataReceived(const utils::Buffer& b);

  private:
    ITagInterpreter<Tag>* m_interpreter;
    Tag m_tag;

    ISender* m_sender;
  };
  
}

#include "net/tagger.cpp"

#endif
