#ifndef INCLUDED_IMODULE_CLASS_SPEC
#define INCLUDED_IMODULE_CLASS_SPEC

#include <string>
#include <vector>

namespace utils {
  class Buffer;
}

/**
 * Contains some information about a moduleclass.
 * Only those attributes of a moduleclass that are relevant for
 * the model are stored in it.
 */
class IModuleClassSpec
{
public:
	virtual ~IModuleClassSpec() {};

	virtual const std::string& moduleClassName() const=0;

  /**
   * Returns the types of all inputs.
   * @return a vector v with v.size() == numberOfInputs and
   *         v[i] == "type of input i" for 0 <= i < numberOfInputs
   */
	virtual const std::vector<int>& inputs() const=0;

  /**
   * Returns the types of all outputs.
   * @return a vector v with v.size() == numberOfOutputs and
   *         v[i] == "type of output i" for 0 <= i < numberOfOutputs
   */
	virtual const std::vector<int>& outputs() const=0;

  /**
   * Returns the serialized defaultvalue of an input.
   * @param input the number of the input for which the defaultvalue
   *              is returned
   * @return a buffer with the serialized value
   */
	virtual const utils::Buffer& defaultValue(int input) const = 0;

  /**
   * Copies the ModleClassSpec.
   * @return a copy of *this.
   */
	virtual IModuleClassSpec* clone() const =0;

        /**
         * \throws std::invalid_argument if the id is not valid.
         */
        virtual int indexFromInputID(const std::string& id) const = 0;

        /**
         * \throws std::invalid_argument if the id is not valid.
         */
        virtual int indexFromOutputID(const std::string& id) const = 0;

  /**
   * \throws std::invalid_argument if the index is not valid.
   */
  virtual std::string inputID(int index) const = 0;

  /**
   * \throws std::invalid_argument if the index is not valid.
   */
  virtual std::string outputID(int index) const = 0;
};

#endif
