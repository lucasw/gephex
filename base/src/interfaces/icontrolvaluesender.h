#ifndef INCLUDED_ICONTROLVALUESENDER_H
#define INCLUDED_ICONTROLVALUESENDER_H
class IControlValueReceiver;
class IControlValueSender
{
 public:
  virtual void registerControlValueReceiver(IControlValueReceiver& r) = 0;
};

#endif
