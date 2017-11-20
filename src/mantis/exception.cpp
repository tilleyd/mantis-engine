/*==============================================================================
 * ME_Exception implementation
 *     Modified: 2017 Nov 20
 *============================================================================*/

#include "mantis_exception.h"
using std::string;

ME_Exception::ME_Exception(string mesg)
	: _mesg(mesg)
{}

const string& ME_Exception::getMessage() const
{
	return _mesg;
}
