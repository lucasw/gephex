#include "c_type.h"

#include "c_typetables.h"

#include "utils/buffer.h"
#include "utils/autoptr.h"

CType::CType(void* instance_ , const CTypeVTable& ftab ,bool isOwner)
  :	vTab(&ftab), instance(instance_), amOwner(isOwner)
{
}

CType::~CType()
{	
  if (amOwner)
    {		
      vTab->deleteInstance(instance);
    }
}

void CType::assign(const IType* t_)
{	
  // assign is only allowed if both types are equal
  assert(vTab==static_cast<const CType*>(t_)->vTab);

  const CType* t = static_cast<const CType*>(t_);

  vTab->assign(instance,t->instance);
}
		
bool CType::serialize(utils::Buffer& b) const
{
  if (vTab->serialize == 0)
    return false;

  int neededLen = vTab->serialize(instance,0,0);
  if (neededLen <= 0)
    return false;

  char* data = new char[neededLen];
  try
    {
      int len = vTab->serialize(instance, data, neededLen);
      
      b = utils::Buffer(reinterpret_cast<const unsigned char*>(data), len);
      delete[] data;
      return true;
    }
  catch(...)
    {
      delete[] data;
      throw;
    }
}

void CType::deSerialize (const utils::Buffer& buf)
{
	vTab->deSerialize(reinterpret_cast<const char*>(buf.getPtr()),
			  buf.getLen(),instance);
}

void* CType::getPointer() const
{
	return instance;
}

bool CType::equalAttributes(const TypeAttributes& attr) const
{
	return vTab->attributesEqual(instance,const_cast<void*>(static_cast<const void*>(&attr)));
}

void CType::convert(const IType& src,const TypeAttributes& attr)
{
  const CType* src_ = static_cast<const CType*>(&src);

  assert(src_ == dynamic_cast<const CType*>(&src));
  
  if (src_ == 0)
    throw std::runtime_error("Cant convert 0 type in "
			     "CType::convert()");
  
  //TODO: test if the types match
  vTab->convertType(instance,src_->getPointer(),
		    const_cast<void*>(static_cast<const void*>(&attr)));
}
