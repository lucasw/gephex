#include "c_type.h"

#include "c_typetables.h"

#include "utils/buffer.h"
#include "utils/autoptr.h"

CType::CType(void* instance_, CTypeVTable& ftab,bool isOwner)
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
  const CType* t = static_cast<const CType*>(t_);
  assert(t == dynamic_cast<const CType*>(t_)); //HACK
  vTab->assign(instance,t->getPointer());
}
		
utils::Buffer CType::serialize() const
{
  if (vTab->serialize != 0)
    {
      int neededLen = vTab->serialize(instance,0,0);
      utils::AutoPtr<char> data(new char[neededLen]);
      vTab->serialize(instance,data.c_ptr(),neededLen);
      
      utils::Buffer ret(reinterpret_cast<const unsigned char*>(data.c_ptr()),
			neededLen);

      return ret;
    }
  else
    {
      return utils::Buffer(reinterpret_cast<const unsigned char*>(""),1);
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
