#ifndef INCLUDED_ITYPECLASSNAMESENDER_H
#define INCLUDED_ITYPECLASSNAMESENDER_H
class ITypeClassNameReceiver;
class ITypeClassNameSender
{
 public:
  virtual void registerTypeClassNameReceiver(ITypeClassNameReceiver& r) = 0;
};

#endif
