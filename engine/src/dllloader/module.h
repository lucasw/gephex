#ifndef INCLUDED_MODULE_H
#define INCLUDED_MODULE_H

/**
 * Common module interface for our own modules and other apis
 * (e.g. freeframe)
 * These modules are typically created by a metamodule
 */
class Module
{
 public:
  virtual ~Module() {};

  //TODO void* must become Type*!
  virtual void setInput(int index, void* type) = 0;
  virtual void setOutput(int index, void* type) = 0;

  virtual void update() = 0;
	
  virtual void strongDependenciesCalculated(int** neededIns) = 0;
  virtual void getPatchLayout(int** out2in ) = 0;
};
#endif
