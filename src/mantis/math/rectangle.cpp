/*==============================================================================
 * ME_Rectangle implementation
 *============================================================================*/

#include "mantis_math.h"

ME_Rectangle::ME_Rectangle(int x, int y, int w, int h)
    : _x(x)
    , _y(y)
    , _w(w)
    , _h(h)
{}

void ME_Rectangle::setX(int x)
{
    _x = x;
}

void ME_Rectangle::setY(int y)
{
    _y = y;
}

void ME_Rectangle::setWidth(int w)
{
    _w = w;
}

void ME_Rectangle::setHeight(int h)
{
    _h = h;
}

int ME_Rectangle::getX() const
{
    return _x;
}

int ME_Rectangle::getY() const
{
    return _y;
}

int ME_Rectangle::getWidth() const
{
    return _w;
}

int ME_Rectangle::getHeight() const
{
    return _h;
}

/*bool ME_Rectangle::collidesWithPoint(int x, int y) const
{
    return (x >= _x && x <= (_x + _w)) && (y >= _y && y <= (_y + _h));
}*/

/*bool ME_Rectangle::collidesWithRectangle(const ME_Rectangle* rect) const
{

}*/

SDL_Rect ME_Rectangle::getSDLRect() const
{
    SDL_Rect rect;
    rect.x = _x;
    rect.y = _y;
    rect.w = _w;
    rect.h = _h;
    return rect;
}
