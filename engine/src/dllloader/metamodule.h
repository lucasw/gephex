#ifndef INCLUDED_META_MODULE_H
#define INCLUDED_META_MODULE_H

#include <string>

namespace utils
{
  class ILogger;
}

class Module;

/**
 * Common module interface for our own meta-modules and other apis
 * (e.g. freeframe)
 */

class MetaModule
{
 public:
  MetaModule(utils::ILogger& logger);
  virtual ~MetaModule();

  /**
   * Important: the MetaModule must live at least as long as
   * the "oldest" Module it has created!
   */
  virtual Module* createModule() = 0;

  virtual std::string getInfo() const = 0;

  virtual std::string getSpec() const = 0;
  virtual std::string getInputSpec(int index) const = 0;
  virtual std::string getOutputSpec(int index) const = 0;

  //TODO: void*!!!
  virtual void* getInputAttributes(int index) const = 0;

protected:
  utils::ILogger& m_logger;
};
#endif
