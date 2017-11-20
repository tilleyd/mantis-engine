/*==============================================================================
 * Demo Program. The framework is set up here, see the respective stage classes
 * for more details on how the demo works.
 *============================================================================*/

#include <iostream>
#include "mantis/mantis.h"

#include "menu.h"

int main(int argc, char* argv[])
{
	// attempt to create the framework
	ME_Framework* fw = NULL;
	try {
		fw = new ME_Framework("mantisdemo", "Mantis indev Demo");
	} catch (ME_Exception e) {
		std::cout << "Error: " << e.getMessage() << std::endl;
		return 1;
	}

	// create the stages
	ME_Stage* menu = new Menu(fw);
	fw->addStage(menu, "st_menu");
	fw->setActiveStage("st_menu");

	// start the demo at 60 FPS
	fw->start(60);

	// clean up
	delete fw;
	fw = NULL;
}
