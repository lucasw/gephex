#ifndef INCLUDED_ITYPECLASSLOADERCONTROLSENDER_H
#define INCLUDED_ITYPECLASSLOADERCONTROLSENDER_H
class ITypeClassLoaderControlReceiver;
class ITypeClassLoaderControlSender
{
 public:
  virtual void registerTypeClassLoaderControlReceiver(ITypeClassLoaderControlReceiver& r) = 0;
};

#endif
