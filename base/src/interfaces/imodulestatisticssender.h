#ifndef INCLUDED_IMODULESTATISTICSSENDER_H
#define INCLUDED_IMODULESTATISTICSSENDER_H
class IModuleStatisticsReceiver;
class IModuleStatisticsSender
{
 public:
  virtual void registerModuleStatisticsReceiver(IModuleStatisticsReceiver& r) = 0;
};

#endif
