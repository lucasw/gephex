#ifndef INCLUDED_IMODULESTATISTICSSMARTSENDER_H
#define INCLUDED_IMODULESTATISTICSSMARTSENDER_H
class IModuleStatisticsSmartReceiver;
class IModuleStatisticsSmartSender
{
 public:
  virtual void registerModuleStatisticsSmartReceiver(IModuleStatisticsSmartReceiver& r) = 0;
};

#endif
