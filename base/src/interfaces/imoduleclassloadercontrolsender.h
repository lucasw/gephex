#ifndef INCLUDED_IMODULECLASSLOADERCONTROLSENDER_H
#define INCLUDED_IMODULECLASSLOADERCONTROLSENDER_H
class IModuleClassLoaderControlReceiver;
class IModuleClassLoaderControlSender
{
 public:
  virtual void registerModuleClassLoaderControlReceiver(IModuleClassLoaderControlReceiver& r) = 0;
};

#endif
