#ifndef INCLUDED_ITYPECLASSINFOSENDER_H
#define INCLUDED_ITYPECLASSINFOSENDER_H
class ITypeClassInfoReceiver;
class ITypeClassInfoSender
{
 public:
  virtual void registerTypeClassInfoReceiver(ITypeClassInfoReceiver& r) = 0;
};

#endif
