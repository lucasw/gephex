#ifndef INCLUDED_ISEQUENCERSTATUSSENDER_H
#define INCLUDED_ISEQUENCERSTATUSSENDER_H
class ISequencerStatusReceiver;
class ISequencerStatusSender
{
 public:
  virtual void registerSequencerStatusReceiver(ISequencerStatusReceiver& r) = 0;
};

#endif
