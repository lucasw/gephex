#ifndef INCLUDED_MODULE_CLASS_SPEC_H
#define INCLUDED_MODULE_CLASS_SPEC_H

#include <vector>
#include "../interfaces/imoduleclassspec.h"

class ModuleClassSpec : public IModuleClassSpec
{
public:
	ModuleClassSpec(int mClassID, const std::vector<int>& ins,const std::vector<int>& outs);
	virtual ~ModuleClassSpec() {};

	virtual const int moduleClassID() const;
	virtual const std::vector<int>& inputs() const;
	virtual const std::vector<int>& outputs() const;

	virtual IModuleClassSpec* clone() const;
	
private:
	std::vector<int> m_inputs;
	std::vector<int> m_outputs;
	int m_moduleClassID;
};

#endif

