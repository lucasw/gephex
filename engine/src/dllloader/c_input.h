#ifndef INCLUDED_INPUT_H
#define INCLUDED_INPUT_H

#include "interfaces/imodule.h"

class ITypeFactory;

namespace utils {
	class Buffer;
}

class CInputVTable;

class CInput : public IInput
{
public:	
	/**
	* defaultValue must exist at least as long as this instance.
	* TODO: make defaultValue a static IType that is shared
	* among all modules of the same kind.
	*/
	CInput(int _typeID,bool _const,bool _strong,
	       IModule&, int index, const ITypeFactory& factory_,
		   const TypeAttributes* attr, IType& defaultValue,
		   const CInputVTable& vtable, void* instance);

	virtual ~CInput();

	virtual const IType* getData() const;

	virtual IModule* getConnectedModule() const;

	//	virtual bool hasChanged() const;

	virtual void plugIn(utils::AutoPtr<IOutputPlug>& oPlug)
	  throw (std::runtime_error);

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
	utils::AutoPtr<IOutputPlug> oPlug;
	int typeID;
	bool _isConst;
	bool _isStrong;
	IModule* mod;
  int m_index;
	//	mutable bool changed;
	const ITypeFactory* factory;
	const TypeAttributes* m_attr;

	const CInputVTable* m_vtable;
	void* m_instance;
};

#endif
