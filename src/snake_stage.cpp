/*==============================================================================
 * Demo Program. Implementation of SnakeStage.
 *============================================================================*/

#include "snake.h"

#include <cmath>
#include <ctime>
#include <sstream>

#include <iostream>
using namespace std;

// window size of 720x720 allows 24px 30x30 grid
#define TILE_SIZE 24
#define FIELD_SIZE 30
#define START_LENGTH 5

SnakeStage::SnakeStage(ME_Framework* fw):
    ME_Stage(fw),
    _gameover(false),
    _score(0)
{
    _width = fw->getWidth();
    _height = fw->getHeight();
    // create the snake entity
    _snake = new Snake();
    addEntity(_snake, "en_snake");
    // place the starting pill
    srand(time(0));
    placePill();
}

void SnakeStage::update(double period)
{
    if (!_gameover) {
        // update the entities (only the snake in this case)
        updateEntities(period);
        // check collisions
        if (_snake->touchHead(_pill)) {
            _snake->increaseLength();
            ++_score;
            placePill();
        }
        if (_snake->gameOver()) {
            _gameover = true;
        }
    }
}

void SnakeStage::render(ME_Graphics* g)
{
    g->setColor(47, 52, 63);
    g->clear();
    // render the entities (only the snake in this case)
    renderEntities(g);
    // render the pill
    g->setColor(132, 193, 92);
    g->fillRect(_pill.x * TILE_SIZE, _pill.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    // render the score
    std::stringstream text;
    text << "Score: " << _score;
    g->setColor(255, 255, 255);
    g->drawText(TILE_SIZE, TILE_SIZE, text.str());
}

void SnakeStage::onKeyPress(SDL_KeyboardEvent* evt)
{
    int dir = -1;
    switch (evt->keysym.sym) {
        case SDLK_SPACE:
            _framework->setHoverStage("hst_pause", false);
        case SDLK_RIGHT:
            dir = DIR_RIGHT;
            break;
        case SDLK_LEFT:
            dir = DIR_LEFT;
            break;
        case SDLK_UP:
            dir = DIR_UP;
            break;
        case SDLK_DOWN:
            dir = DIR_DOWN;
            break;
        case SDLK_ESCAPE:
            _framework->stop();
            break;
    }
    if (dir != -1) {
        _snake->setDirection(dir);
    }
}

void SnakeStage::allocateResources(ME_Graphics* g)
{
    g->setFont("font/Hack.ttf", TILE_SIZE);
}

void SnakeStage::deallocateResources()
{}

void SnakeStage::placePill()
{
    do {
        _pill.x = (rand() % FIELD_SIZE);
        _pill.y = (rand() % FIELD_SIZE);
    } while (_snake->touchBody(_pill));
}
