#ifndef INCLUDED_ISEQUENCENAMESENDER_H
#define INCLUDED_ISEQUENCENAMESENDER_H
class ISequenceNameReceiver;
class ISequenceNameSender
{
 public:
  virtual void registerSequenceNameReceiver(ISequenceNameReceiver& r) = 0;
};

#endif
