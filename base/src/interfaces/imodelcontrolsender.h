#ifndef INCLUDED_IMODELCONTROLSENDER_H
#define INCLUDED_IMODELCONTROLSENDER_H
class IModelControlReceiver;
class IModelControlSender
{
 public:
  virtual void registerModelControlReceiver(IModelControlReceiver& r) = 0;
};

#endif
