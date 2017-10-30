/*==============================================================================
 * Demo Program
 *     Author  : Duncan Tilley
 *     Modified: 2017 Oct 30
 *============================================================================*/

#include <iostream>
#include "mantis.h"

int main(int argc, char* argv[])
{
	// attempt to create the framework
	ME_Framework* fw = NULL;
	try {
		fw = new ME_Framework("mantisdemo", "Mantis indev Demo");
	} catch (ME_Exception e) {
		std::cout << "Error: " << e.getMessage() << std::endl;
	}
	// start the timer
	fw->start(60);
	// clean up
	if (fw) {
		delete fw;
		fw = NULL;
	}
}
