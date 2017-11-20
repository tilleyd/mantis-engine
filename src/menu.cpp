/*==============================================================================
 * Demo Program. Implementation of Menu.
 *============================================================================*/

#include "menu.h"

Menu::Menu(ME_Framework* fw)
    : ME_Stage(fw)
{
    _framework->getImageBank()->loadImage("res/mantis.png", "img_mantis");
    _mantis = _framework->getImageBank()->getImage("img_mantis");
    _width = _framework->getWidth();
    _height = _framework->getHeight();
    _xspeed = _yspeed = 4;
    _imgx = _imgy = 0;
}

void Menu::update(double period)
{
    _imgx += _xspeed;
    _imgy += _yspeed;
    if ((_xspeed < 0 && _imgx <= 0) ||
            (_xspeed > 0 && (_imgx + _mantis->getWidth()) >= _width)) {
        _xspeed = -_xspeed;
    }
    if ((_yspeed < 0 && _imgy <= 0) ||
            (_yspeed > 0 && (_imgy + _mantis->getHeight()) >= _height)) {
        _yspeed = -_yspeed;
    }
}

void Menu::render(ME_Graphics* g)
{
    g->setColor(208, 227, 232);
    g->clear();
    g->drawImage(_mantis, _imgx, _imgy);
}
