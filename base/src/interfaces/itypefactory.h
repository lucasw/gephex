#ifndef INCLUDED_ITYPE_FACTORY_H
#define INCLUDED_ITYPE_FACTORY_H

class IType;

/**
 * Abstract base class for factories that assemble types identified by
 * ids.
 */
class ITypeFactory
{
public:
  virtual ~ITypeFactory() {};


  /**
   * Returns a new type instance with a specific id.
   * If id is unknown to the factory the behaviour is undefined.
   * @param id the id (= "class") of the type that is created
   * @return pointer to a new type object
   */
  virtual IType* buildNew(int id) const = 0;
};

#endif

