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
		fw->addStage(new SnakeStage(fw), "st_snake");
		fw->addStage(new PauseStage(fw), "hst_pause");
		fw->setActiveStage("st_snake");
		fw->setWindowMode(WM_WINDOWED);

		// start the demo with VSync enabled
		fw->start(FPS_VSYNC);

		// clean up
		delete fw;
		fw = NULL;
	} catch (ME_Exception e) {
		std::cout << "Error: " << e.getMessage() << std::endl;
		return 1;
	}
}
