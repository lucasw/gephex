#ifndef INCLUDED_IMODULECLASSSENDER_H
#define INCLUDED_IMODULECLASSSENDER_H
class IModuleClassReceiver;
class IModuleClassSender
{
 public:
  virtual void registerModuleClassReceiver(IModuleClassReceiver& r) = 0;
};

#endif
