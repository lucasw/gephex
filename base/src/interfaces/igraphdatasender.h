#ifndef INCLUDED_IGRAPHDATASENDER_H
#define INCLUDED_IGRAPHDATASENDER_H
class IGraphDataReceiver;
class IGraphDataSender
{
 public:
  virtual void registerGraphDataReceiver(IGraphDataReceiver& r) = 0;
};

#endif
