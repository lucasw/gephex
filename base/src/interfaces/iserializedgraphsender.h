#ifndef INCLUDED_ISERIALIZEDGRAPHSENDER_H
#define INCLUDED_ISERIALIZEDGRAPHSENDER_H
class ISerializedGraphReceiver;
class ISerializedGraphSender
{
 public:
  virtual void registerSerializedGraphReceiver(ISerializedGraphReceiver& r) = 0;
};

#endif
