#ifndef INCLUDED_ITYPECLASSSENDER_H
#define INCLUDED_ITYPECLASSSENDER_H
class ITypeClassReceiver;
class ITypeClassSender
{
 public:
  virtual void registerTypeClassReceiver(ITypeClassReceiver& r) = 0;
};

#endif
