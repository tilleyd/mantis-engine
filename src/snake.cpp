/*==============================================================================
 * Demo Program. Implementation of Snake.
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

Snake::Snake(ME_Framework* fw)
    : ME_Stage(fw)
    , _gameover(false)
    , _body()
    , _dir(3)
    , _newdir(3)
    , _length(START_LENGTH)
    , _alength(0)
    , _score(0)
{
    _width = fw->getWidth();
    _height = fw->getHeight();
    // start in the center
    _head.x = FIELD_SIZE / 2;
    _head.y = FIELD_SIZE / 2;
    // place the starting pill
    srand(time(0));
    placePill();
    // create the test ui component
    ME_UiComponent* c = new ME_UiButton("Pause");
    c->setPosition(10, 200);
    addUiComponent(c, "ui_test");
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
        // check collisions
        if (_pill.x == _head.x && _pill.y == _head.y) {
            ++_length;
            ++_score;
            placePill();
        }
        if (touchBody(_head)) {
            _gameover = true;
        }
    }
}

void Snake::render(ME_Graphics* g)
{
    g->setColor(47, 52, 63);
    g->clear();
    // render the body
    g->setColor(94, 158, 193);
    for (unsigned int i = 0; i < _body.size(); ++i) {
        point_t& cur = _body[i];
        g->fillRect(cur.x * TILE_SIZE, cur.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }
    // render the pill
    g->setColor(132, 193, 92);
    g->fillRect(_pill.x * TILE_SIZE, _pill.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    // render the head
    g->setColor(208, 223, 112);
    g->fillRect(_head.x * TILE_SIZE, _head.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    // render the score
    std::stringstream text;
    text << "Score: " << _score;
    g->setColor(255, 255, 255);
    g->drawText(TILE_SIZE, TILE_SIZE, text.str());
    renderUiComponents(g);
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
        case SDLK_ESCAPE:
            _framework->stop();
            break;
    }
}

bool Snake::touchBody(const point_t& point) const
{
    unsigned int i = 0;
    while (i < _body.size()) {
        const point_t& cur = _body[i++];
        if (cur.x == point.x && cur.y == point.y) {
            return true;
        }
    }
    return false;
}

void Snake::placePill()
{
    do {
        _pill.x = (rand() % FIELD_SIZE);
        _pill.y = (rand() % FIELD_SIZE);
    } while (touchBody(_pill));
}

void Snake::allocateResources(ME_Graphics* g)
{
    g->setFont("font/Hack.ttf", TILE_SIZE);
    ME_UiButton* btn = (ME_UiButton*)(getUiComponent("ui_test"));
    btn->adjustSizeToFont(g);
}

void Snake::deallocateResources()
{}
