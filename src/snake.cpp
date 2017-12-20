/*==============================================================================
 * Demo Program. Implementation of Snake.
 *============================================================================*/

#include "snake.h"

Snake::Snake():
    _body(),
    _dir(3),
    _newdir(3),
    _length(START_LENGTH),
    _alength(0)
{
    // start in the center
    _head.x = FIELD_SIZE / 2;
    _head.y = FIELD_SIZE / 2;
}

void Snake::update(double period)
{
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

void Snake::render(ME_Graphics* g)
{
    // render the body
    g->setColor(94, 158, 193);
    for (unsigned int i = 0; i < _body.size(); ++i) {
        point_t& cur = _body[i];
        g->fillRect(cur.x * TILE_SIZE, cur.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }
    // render the head
    g->setColor(208, 223, 112);
    g->fillRect(_head.x * TILE_SIZE, _head.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
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

bool Snake::touchHead(const point_t& point) const
{
    return (point.x == _head.x && point.y == _head.y);
}

bool Snake::gameOver() const
{
    return touchBody(_head);
}

void Snake::setDirection(int dir)
{
    _newdir = dir;
}

void Snake::increaseLength()
{
    ++_length;
}
