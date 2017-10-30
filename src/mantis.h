/*==============================================================================
 * Mantis Engine main class headers
 *     Author  : Duncan Tilley
 *     Modified: 2017 Oct 30
 *============================================================================*/

#ifndef ME_MANTIS_H
#define ME_MANTIS_H

#include <string>

/*------------------------------------------------------------------------------
 * ME_Window
 *
 *     Creates a window using the SDL2 library with the provided width and
 *     height.
 *----------------------------------------------------------------------------*/
class ME_Window
{
	public:
		ME_Window(unsigned int w, unsigned int h);
};

/*------------------------------------------------------------------------------
 * ME_Exception
 *
 *     Represents an exception/error used for try/catch statements. Contains
 *     an error message string.
 *----------------------------------------------------------------------------*/
class ME_Exception
{
	public:
		ME_Exception(std::string);
		const std::string& getMessage() const;
	private:
		std::string _mesg;
};

#endif
