#ifndef INCLUDED_IMODULE_CLASS_VIEW
#define INCLUDED_IMODULE_CLASS_VIEW

namespace gui
{
	class ModuleInfo;

	class IModuleClassView
	{
	public:
		virtual ~IModuleClassView() {};
		virtual void moduleClassLoaded(const std::string& moduleClassName,const ModuleInfo& mi) = 0;
		virtual void moduleClassUnloaded(const std::string& moduleClassName) = 0;
	};
}

#endif
