/*==============================================================================
 * Demo Program
 *     Author  : Duncan Tilley
 *     Modified: 2017 Oct 30
 *============================================================================*/

#include <iostream>
#include "mantis.h"
#include "mantis_timing.h"

int main(int argc, char* argv[])
{
	// attempt to create a new window
	ME_Window* window = NULL;
	try {
		window = new ME_Window("Mantis Engine Demo", 1280, 720);
	} catch (ME_Exception e) {
		std::cout << "Error: " << e.getMessage() << std::endl;
	}
	// start the timer
	// TODO
	// clean up
	if (window) {
		delete window;
		window = NULL;
	}
}
