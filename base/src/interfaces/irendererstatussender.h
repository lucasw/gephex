#ifndef INCLUDED_IRENDERERSTATUSSENDER_H
#define INCLUDED_IRENDERERSTATUSSENDER_H
class IRendererStatusReceiver;
class IRendererStatusSender
{
 public:
  virtual void registerRendererStatusReceiver(IRendererStatusReceiver& r) = 0;
};

#endif
