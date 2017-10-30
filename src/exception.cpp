/*==============================================================================
 * ME_Exception implementation
 *     Author  : Duncan Tilley
 *     Modified: 2017 Oct 30
 *============================================================================*/

#include "mantis.h"
using std::string;

ME_Exception::ME_Exception(string mesg)
	: _mesg(mesg)
{}

const string& ME_Exception::getMessage() const
{
	return _mesg;
}
