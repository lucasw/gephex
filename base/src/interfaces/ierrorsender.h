#ifndef INCLUDED_IERRORSENDER_H
#define INCLUDED_IERRORSENDER_H
class IErrorReceiver;
class IErrorSender
{
 public:
  virtual void registerErrorReceiver(IErrorReceiver& r) = 0;
};

#endif
