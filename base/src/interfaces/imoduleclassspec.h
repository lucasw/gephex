/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

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
