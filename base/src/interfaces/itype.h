#ifndef INCLUDED_ITYPE_H
#define INCLUDED_ITYPE_H

namespace utils 
{ 
  class Buffer; 
}

class TypeAttributes;

/**
 * This is the abstract base class for types that are passed between
 * modules.
 */
class IType
{
 public: 
  virtual ~IType() {}

  /**
   * Copy the contents of t into *this. Wether this is a deep or a shallow
   * copy depends on the concrete type.
   * @param t the IType that is to be copied
   */
  virtual void assign(const IType* t) = 0;
	
  /**
   * Serializes a type.
   * @return a Buffer that contains the serialized type
   */
  virtual bool serialize (utils::Buffer& b) const = 0;

  /**
   * Deserialize the contents of a Buffer and assign them to *this.
   * This is rather a constructor than a normal method.
   * @buf the Buffer that contains the serialized data.
   */
  virtual void deSerialize (const utils::Buffer& buf) = 0;

  //doof!
  virtual bool equalAttributes(const TypeAttributes& attr) const = 0;

  virtual void convert(const IType& src, const TypeAttributes& attr) = 0;

  /*
   * Returns a void pointer to the internal Type instance.
   * This pointer should only be used by the modules. DONT USE! 
   * This is going to change.  It makes sense only for
   * types that are loaded as c dll plugins. For c++ types there
   * might be no internal pointer they should return the this pointer
   * TODO!!!!
   * @return pointer to the real type instance.
   */
  virtual void* getPointer() const = 0;
  
};

#endif
