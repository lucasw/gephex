#ifndef INCLUDED_IMODULECONSTRUCTIONSMARTSENDER_H
#define INCLUDED_IMODULECONSTRUCTIONSMARTSENDER_H
class IModuleConstructionSmartReceiver;
class IModuleConstructionSmartSender
{
 public:
  virtual void registerModuleConstructionSmartReceiver(IModuleConstructionSmartReceiver& r) = 0;
};

#endif
