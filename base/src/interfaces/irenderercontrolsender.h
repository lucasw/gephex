#ifndef INCLUDED_IRENDERERCONTROLSENDER_H
#define INCLUDED_IRENDERERCONTROLSENDER_H
class IRendererControlReceiver;
class IRendererControlSender
{
 public:
  virtual void registerRendererControlReceiver(IRendererControlReceiver& r) = 0;
};

#endif
