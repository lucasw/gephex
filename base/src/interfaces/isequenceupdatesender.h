#ifndef INCLUDED_ISEQUENCEUPDATESENDER_H
#define INCLUDED_ISEQUENCEUPDATESENDER_H
class ISequenceUpdateReceiver;
class ISequenceUpdateSender
{
 public:
  virtual void registerSequenceUpdateReceiver(ISequenceUpdateReceiver& r) = 0;
};

#endif
