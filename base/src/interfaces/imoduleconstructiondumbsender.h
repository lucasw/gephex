#ifndef INCLUDED_IMODULECONSTRUCTIONDUMBSENDER_H
#define INCLUDED_IMODULECONSTRUCTIONDUMBSENDER_H
class IModuleConstructionDumbReceiver;
class IModuleConstructionDumbSender
{
 public:
  virtual void registerModuleConstructionDumbReceiver(IModuleConstructionDumbReceiver& r) = 0;
};

#endif
