#ifndef INCLUDED_IMODULECLASSSPECSENDER_H
#define INCLUDED_IMODULECLASSSPECSENDER_H
class IModuleClassSpecReceiver;
class IModuleClassSpecSender
{
 public:
  virtual void registerModuleClassSpecReceiver(IModuleClassSpecReceiver& r) = 0;
};

#endif
