#ifndef INCLUDED_IMODULECLASSNAMESENDER_H
#define INCLUDED_IMODULECLASSNAMESENDER_H
class IModuleClassNameReceiver;
class IModuleClassNameSender
{
 public:
  virtual void registerModuleClassNameReceiver(IModuleClassNameReceiver& r) = 0;
};

#endif
