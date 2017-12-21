/*==============================================================================
 * Demo Program. Implementation of PauseStage.
 *============================================================================*/

#include "snake.h"

PauseStage::PauseStage(ME_Framework* fw):
    ME_Stage(fw)
{
    _width = fw->getWidth();
    _height = fw->getHeight();
}

void PauseStage::update(double period)
{}

void PauseStage::render(ME_Graphics* g)
{
    //g->setColor(47, 52, 63, 100);
    //g->fillRect(0, 0, _width, _height);
    // render the text
    g->setColor(255, 255, 255);
    g->drawText(TILE_SIZE, TILE_SIZE * 2, "Press <space> to continue...");
}

void PauseStage::onKeyPress(SDL_KeyboardEvent* evt)
{
    switch (evt->keysym.sym) {
        case SDLK_SPACE:
            _framework->clearHoverStage();
            break;
        case SDLK_ESCAPE:
            _framework->stop();
            break;
    }
}

void PauseStage::allocateResources(ME_Graphics* g)
{
    g->setFont("font/Hack.ttf", TILE_SIZE);
}

void PauseStage::deallocateResources()
{}
