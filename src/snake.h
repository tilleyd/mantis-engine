/*==============================================================================
 * Demo Program. This is the snake game stage class.
 *============================================================================*/

#ifndef DEMO_SNAKE_H
#define DEMO_SNAKE_H

#include "mantis/mantis.h"
#include <deque>

struct point_t
{
    int x;
    int y;
};

class Snake : public ME_Stage
{
    public:
        Snake(ME_Framework*);

        /*----------------------------------------------------------------------
         * Override from ME_Stage                                             */
        void update(double);
        void render(ME_Graphics*);

        /*----------------------------------------------------------------------
         * Event polling functions                                            */
        void onKeyPress(SDL_KeyboardEvent*);
    private:
        ME_Image* _mantis;
        int       _width;
        int       _height;

        // precalculated direction array
        int       _xchange[4];
        int       _ychange[4];

        // variables
        bool                _gameover;
        std::deque<point_t> _body;
        point_t             _head;
        int                 _dir;
        int                 _newdir;
        int                 _length;
        int                 _alength;
};

#endif
