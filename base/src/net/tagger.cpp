#include "tagger.h"

namespace net {
  
  template <typename Tag, typename TagUtil>
  Tagger<Tag, TagUtil>::Tagger()
    : m_interpreter(0)
  {
  }

  template <typename Tag, typename TagUtil>
  Tagger<Tag, TagUtil>::Tagger(ITagInterpreter<Tag>& i)
    : m_interpreter(&i)
  {
  }

  template <typename Tag, typename TagUtil>
  void Tagger<Tag, TagUtil>::registerInterpreter(ITagInterpreter<Tag>& i)
  {
    m_interpreter = &i;
  }

  template <typename Tag, typename TagUtil>
  void Tagger<Tag, TagUtil>::registerSender(ISender& s)
  {
    m_sender = &s;
  }
 
  template <typename Tag, typename TagUtil>
  void Tagger<Tag, TagUtil>::setTag(const Tag& t)
  {
    m_tag = t;
  }

  template <typename Tag, typename TagUtil>
  int Tagger<Tag, TagUtil>::send(const utils::Buffer& b)
  {
    utils::Buffer taggedData;
    TagUtil::attachTag(taggedData, m_tag, b);

    return m_sender->send(taggedData);
  }

  template <typename Tag, typename TagUtil>
  void Tagger<Tag, TagUtil>::dataReceived(const utils::Buffer& taggedData)
  {
    Tag tag;
    utils::Buffer data;

    //TODO: exceptions???
    TagUtil::removeTag(data, tag, taggedData);

    m_interpreter->dataReceived(tag, data);
  }

}
