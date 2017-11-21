/*==============================================================================
 * Demo Program. Implementation of Snake.
 *============================================================================*/

#include "snake.h"

// window size of 720x720 allows 24px 30x30 grid
#define TILE_SIZE 24
#define FIELD_SIZE 30
#define START_LENGTH 5

Snake::Snake(ME_Framework* fw)
    : ME_Stage(fw)
    , _gameover(false)
    , _body()
    , _dir(3)
    , _newdir(3)
    , _length(START_LENGTH)
    , _alength(0)
{
    _width = fw->getWidth();
    _height = fw->getHeight();
    // start in the center
    _head.x = FIELD_SIZE / 2;
    _head.y = FIELD_SIZE / 2;
}

void Snake::update(double period)
{
    if (!_gameover) {
        // make sure the snake doesn't do a 180 turn
        if (_newdir != (_dir + 2) % 4) {
            _dir = _newdir;
        }
        point_t prev = _head;
        // calculate the change in position using a hacky method
        int xchange = (_dir - 2) % 2;
        int ychange = (_dir - 1) % 2;
        // move the head
        _head.x = (_head.x + xchange) % FIELD_SIZE;
        _head.y = (_head.y + ychange) % FIELD_SIZE;
        if (_head.x < 0) {
            _head.x += FIELD_SIZE;
        }
        if (_head.y < 0) {
            _head.y += FIELD_SIZE;
        }
        if (_alength == _length) {
            // remove the front segment before adding the new one
            _body.pop_front();
        } else {
            ++_alength;
        }
        _body.push_back(prev);
    }
}

void Snake::render(ME_Graphics* g)
{
    g->setColor(47, 52, 63);
    g->clear();
    // render the head
    g->setColor(208, 223, 112);
    g->fillRect(_head.x * TILE_SIZE, _head.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    // render the body
    g->setColor(94, 158, 193);
    for (unsigned int i = 0; i < _body.size(); ++i) {
        point_t& cur = _body[i];
        g->fillRect(cur.x * TILE_SIZE, cur.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }
}

void Snake::onKeyPress(SDL_KeyboardEvent* evt)
{
    switch (evt->keysym.sym) {
        case SDLK_RIGHT:
            _newdir = 3;
            break;
        case SDLK_LEFT:
            _newdir = 1;
            break;
        case SDLK_UP:
            _newdir = 0;
            break;
        case SDLK_DOWN:
            _newdir = 2;
            break;
    }
}
