#ifndef INCLUDED_IENGINECONTROLSENDER_H
#define INCLUDED_IENGINECONTROLSENDER_H
class IEngineControlReceiver;
class IEngineControlSender
{
 public:
  virtual void registerEngineControlReceiver(IEngineControlReceiver& r) = 0;
};

#endif
