/*==============================================================================
 * Mantis Engine exception class headers
 *     Modified: 2017 Nov 20
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
