/*==============================================================================
 * Mantis Engine exception class headers
 *==============================================================================
 * This file is part of Mantis Engine.
 *
 * Mantis Engine is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Mantis Engine is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Mantis Engine.  If not, see <http://www.gnu.org/licenses/>.
 *============================================================================*/

#ifndef ME_EXCEPTION_H
#define ME_EXCEPTION_H

#include <string>

/*==============================================================================
 * ME_Exception
 *
 *     Represents an exception/error used for try/catch statements. Contains
 *     an error message string.
 *============================================================================*/
class ME_Exception
{
	public:
		ME_Exception(std::string);
		const std::string& getMessage() const;
	private:
		std::string _mesg;
};

#endif
