#ifndef INCLUDED_IMODELSTATUSSENDER_H
#define INCLUDED_IMODELSTATUSSENDER_H
class IModelStatusReceiver;
class IModelStatusSender
{
 public:
  virtual void registerModelStatusReceiver(IModelStatusReceiver& r) = 0;
};

#endif
