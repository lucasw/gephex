#ifndef INCLUDED_ICONTROL_CONNECT_VIEW
#define INCLUDED_ICONTROL_CONNECT_VIEW

namespace gui
{

class IControlConnectView
{
 public:
  virtual void controlConnected(int nodeID, int inputIndex) = 0;
  virtual void controlDisconnected(int nodeID, int inputIndex) = 0;

};

} // end of namepsace gui

#endif
