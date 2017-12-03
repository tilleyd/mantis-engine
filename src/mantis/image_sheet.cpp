/*==============================================================================
 * ME_ImageSheet implementation
 *============================================================================*/

#include "mantis_image.h"

#include "mantis.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using std::string;

ME_ImageSheet::ME_ImageSheet(ME_Graphics* g, std::string path, int startx,
        int starty, int imgw, int imgh, int rows, int cols, int numimgs)
    : ME_Image(g, path)
    , _bounds()
    , _iwidth(imgw)
    , _iheight(imgh)
    , _frequency(0.0)
    , _current(0)
    , _time(0.0)
{
    // check for size errors
    int minwidth = startx + imgw * rows;
    int minheight = starty + imgh * cols;
    if (_width < minwidth || _height < minheight) {
        throw ME_Exception("The sheet is too small for the required clipping");
    }
    if (rows * cols < numimgs) {
        throw ME_Exception("There are more images than possible for rows*cols");
    }
    if (numimgs < 1) {
        throw ME_Exception("The sheet requires at least one clipped image");
    }
    // set up the clipping rectangles
    int row = 0, col = 0;
    int x, y;
    for (int i = 0; i < numimgs; ++i) {
        x = startx + row * imgw;
        y = starty + col * imgh;
        ++row;
        if (row == rows) {
            row = 0;
            ++col;
        }
        SDL_Rect* rect = new SDL_Rect();
        rect->x = x;
        rect->y = y;
        rect->w = imgw;
        rect->h = imgh;
        _bounds.push_back(rect);
    }
}

ME_ImageSheet::~ME_ImageSheet()
{
    // delete the rectangles
    for (unsigned int i = 0; i < _bounds.size(); ++i) {
		delete _bounds[i];
	}
}

int ME_ImageSheet::getWidth() const
{
    // return the clipped image size
    return _iwidth;
}

int ME_ImageSheet::getHeight() const
{
    // return the clipped image size
    return _iheight;
}

void ME_ImageSheet::draw(ME_Graphics* g)
{
    // render the entire screen with the image
    SDL_RenderCopy(g->getSDLRenderer(), _texture, _bounds[_current], NULL);
}

void ME_ImageSheet::draw(ME_Graphics* g, ME_Rectangle* rect)
{
    // render at the given position with stretching
    SDL_Rect dest = rect->getSDLRect();
    SDL_RenderCopy(g->getSDLRenderer(), _texture, _bounds[_current], &dest);
}

void ME_ImageSheet::setCurrentImage(unsigned int index)
{
    if (index < _bounds.size()) {
        _current = index;
    }
}

void ME_ImageSheet::setAnimationFrequency(double fps)
{
    _frequency = fps;
}

void ME_ImageSheet::updateCurrentImage(double period)
{
    _time += period;
    while (_time >= _frequency) {
        // advance to the next image
        _current = (_current + 1) % _bounds.size();
    }
}
