#include "c_input.h"
#include "c_module.h"

#include "interfaces/itypefactory.h"
#include "interfaces/itype.h"

#undef NDEBUG
#include <cassert>




CInput::CInput(int _typeID,
			   bool _const,
			   bool _strong,
			   CModule& cmod,
			   int index, 
			   const ITypeFactory& factory_,
			   const TypeAttributes* attr,  
			   IType& defaultValue)
			   : m_isConnected(false), // not connected use default value 
			   m_defaultValue(0),			   
			   oPlug(0), 
			   typeID(_typeID), 
			   _isConst(_const), 
			   _isStrong(_strong),
			   mod(&cmod), 
			   m_index(index), 
			   factory(&factory_), 
			   m_attr(attr)
{
	// set input to default value
	{
		
		// create default value buffer
		m_defaultValue = factory->buildNew(typeID);
		
		
		// default value einspielen and create if neccesary
		if (m_attr != 0 && !defaultValue.equalAttributes(*m_attr))
		{ // convert
			m_defaultValue->convert(defaultValue,*m_attr);
		}
		else
		{ // just copy
			m_defaultValue->assign(&defaultValue);
		}
		
		// set defaultvalue
		internalData = factory->buildNew(typeID);
		internalData->assign(m_defaultValue);
		
		
		data = internalData;
		//mod->setData(this);
	}
}

CInput::~CInput()
{
	delete internalData;
}

const IType* CInput::getData() const
{
	return data;
}	

IModule* CInput::getConnectedModule() const
{
	if (oPlug != 0)
		return oPlug->getModule();
	else
		return 0;
}

void CInput::plugIn(IOutputPlug& newOPlug) throw (std::runtime_error)
{
	assert(!m_isConnected);
	assert(oPlug==0);	
	
	oPlug = &newOPlug;

	m_isConnected=true;
}


void CInput::unPlug()
{
	delete oPlug;
	oPlug = 0;

	
	assert(internalData!=0);
	// default value einspielen and convert if neccesary
	internalData->assign(m_defaultValue);
	data = internalData;
	m_isConnected=false;
	mod->setData(this);
	
}

int CInput::getType() const
{
	return typeID;
}

bool CInput::isConst() const
{
	return _isConst;
}

bool CInput::isStrongDependency() const
{
	return _isStrong;
}

void CInput::setValue(const utils::Buffer& serializedData)
{
	if (!m_isConnected)
    {
		assert(internalData!=0);
		internalData->deSerialize(serializedData);
		// convert if different attribs
		if (m_attr != 0 && !internalData->equalAttributes(*m_attr))
		{ // convert
			IType* temp = factory->buildNew(typeID); 
			temp->convert(*internalData,*m_attr);
			delete internalData;
			internalData=temp;
		}
    }
}

int CInput::getIndex() const
{
	return m_index;
}

IModule* CInput::getModule() const
{
	return mod;
}

const TypeAttributes* CInput::getTypeAttributes() const
{
	return m_attr;
}

void CInput::update()
{
	const IType* oldValuePtr = data; // remember to check if ptr has changed	

	
	
	if (m_isConnected)
    { // input is connected
		assert(oPlug != 0);
		const IType* connectedData = oPlug->getData();

		assert(connectedData!=0);
		if (m_attr != 0 && !connectedData->equalAttributes(*m_attr))
		{  // input attribs are fixed and differ a conversion is needed
			assert(internalData!=0);
			
			internalData->convert(*connectedData, *m_attr);
			data=internalData;
		}
		else
		{ // no conversion needed
			data=connectedData;
		}
    }
	else
    { // no input is connected
		
		assert(oPlug==0);
		assert(internalData!=0);
		/*
		if (internalData == 0)
		{ // lazy initialisation of internal buffer
		internalData = factory->buildNew(typeID);
		// default value einspielen
		internalData->assign(&m_defaultValue);
		}
		
		  if (m_attr != 0 && !internalData->equalAttributes(*m_attr))
		  { // module has fixed attribs and they differ from  conversion needed
		  IType* temp = factory->buildNew(typeID);
		  temp->convert(*internalData,*m_attr);
		  delete internalData;
		  internalData = temp;
		  }
		*/
		data = internalData;
    }
	
	
	mod->setData(this);
	
	assert(data!=0);
	assert(m_attr == 0 || data->equalAttributes(*m_attr));
}
