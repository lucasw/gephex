#ifndef INCLUDED_IMODULEDATASENDER_H
#define INCLUDED_IMODULEDATASENDER_H
class IModuleDataReceiver;
class IModuleDataSender
{
 public:
  virtual void registerModuleDataReceiver(IModuleDataReceiver& r) = 0;
};

#endif
