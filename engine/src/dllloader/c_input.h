#ifndef INCLUDED_INPUT_H
#define INCLUDED_INPUT_H

#include "interfaces/imodule.h"

class IModule;
class IOutputPlug;
class IType;
class CModule;
class ITypeFactory;

namespace utils {
	class Buffer;
}

class CInput : public IInput
{
public:	
	/**
	* defaultValue must exist at least as long as this instance.
	* TODO: make defaultValue a static IType that is shared
	* among all modules of the same kind.
	*/
	CInput(int _typeID,bool _const,bool _strong,
	       CModule&, int index, const ITypeFactory& factory_,
		   const TypeAttributes* attr, IType& defaultValue);

	virtual ~CInput();

	virtual const IType* getData() const;

	virtual IModule* getConnectedModule() const;

	//	virtual bool hasChanged() const;

	virtual void plugIn(IOutputPlug&) throw (std::runtime_error);

	virtual void unPlug();

	virtual int getType() const;

	virtual bool isConst() const;

	virtual bool isStrongDependency() const;

	virtual void setValue(const utils::Buffer& serializedData);

	virtual int getIndex() const;

	virtual IModule* getModule() const;

	virtual const TypeAttributes* getTypeAttributes() const;

	virtual void update();

private:
	bool m_isConnected;

	IType* m_defaultValue; // default value
	const IType* data; // pointer to the valid value this is returned to the module
	IType* internalData;	
	IOutputPlug* oPlug;
	int typeID;
	bool _isConst;
	bool _isStrong;
	CModule* mod;
  int m_index;
	//	mutable bool changed;
	const ITypeFactory* factory;
	const TypeAttributes* m_attr;


};

#endif
