/*==============================================================================
 * Demo Program. The framework is set up here, see the respective stage classes
 * for more details on how the demo works.
 *============================================================================*/

#include <iostream>
#include "mantis/mantis.h"

#include "snake.h"

int main(int argc, char* argv[])
{
	// attempt to create the framework
	ME_Framework* fw = NULL;
	try {
		fw = new ME_Framework("Mantis Snake Demo", 720, 720);

		// create the single stage
		ME_Stage* snake = new Snake(fw);
		fw->addStage(snake, "st_snake");
		fw->setActiveStage("st_snake");
		fw->setWindowMode(WM_WINDOWED);

		// start the demo at 8 FPS (nice and slow for snake)
		fw->start(8);

		// clean up
		delete fw;
		fw = NULL;
	} catch (ME_Exception e) {
		std::cout << "Error: " << e.getMessage() << std::endl;
		return 1;
	}
}
