#ifndef INCLUDED_ISEQUENCERCONTROLSENDER_H
#define INCLUDED_ISEQUENCERCONTROLSENDER_H
class ISequencerControlReceiver;
class ISequencerControlSender
{
 public:
  virtual void registerSequencerControlReceiver(ISequencerControlReceiver& r) = 0;
};

#endif
