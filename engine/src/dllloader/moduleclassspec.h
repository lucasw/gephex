#ifndef INCLUDED_MODULE_CLASS_SPEC_H
#define INCLUDED_MODULE_CLASS_SPEC_H

#include <vector>
#include "interfaces/imoduleclassspec.h"

#include "utils/buffer.h" //TODO

class ModuleClassSpec : public IModuleClassSpec
{
public:
	ModuleClassSpec(const std::string& moduleClassName, const std::vector<int>& ins,
					const std::vector<utils::Buffer>& defaultValues,
					const std::vector<int>& outs);
	ModuleClassSpec(const ModuleClassSpec&);
	virtual ~ModuleClassSpec() {};

	virtual const std::string& moduleClassName() const;
	virtual const std::vector<int>& inputs() const;
	virtual const std::vector<int>& outputs() const;
	virtual const utils::Buffer& defaultValue(int input) const;

	virtual IModuleClassSpec* clone() const;
	
private:
	const std::string m_moduleClassName;
	std::vector<int> m_inputs;
	std::vector<int> m_outputs;

	std::vector<utils::Buffer> m_defaultValues;

};

#endif

