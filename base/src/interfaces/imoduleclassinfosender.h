#ifndef INCLUDED_IMODULECLASSINFOSENDER_H
#define INCLUDED_IMODULECLASSINFOSENDER_H
class IModuleClassInfoReceiver;
class IModuleClassInfoSender
{
 public:
  virtual void registerModuleClassInfoReceiver(IModuleClassInfoReceiver& r) = 0;
};

#endif
