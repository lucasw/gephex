#ifndef INCLUDED_IGRAPHNAMESENDER_H
#define INCLUDED_IGRAPHNAMESENDER_H
class IGraphNameReceiver;
class IGraphNameSender
{
 public:
  virtual void registerGraphNameReceiver(IGraphNameReceiver& r) = 0;
};

#endif
