#ifndef INCLUDED_ISMARTCONTROLVALUESENDER_H
#define INCLUDED_ISMARTCONTROLVALUESENDER_H
class ISmartControlValueReceiver;
class ISmartControlValueSender
{
 public:
  virtual void registerSmartControlValueReceiver(ISmartControlValueReceiver& r) = 0;
};

#endif
