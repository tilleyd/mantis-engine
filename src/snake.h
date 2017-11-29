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
        void onActivate(ME_Graphics*);
    private:
        // collision function
        bool touchBody(const point_t&) const;
        void placePill();

        ME_Image* _mantis;
        int       _width;
        int       _height;

        // variables
        bool                _gameover;
        std::deque<point_t> _body;
        point_t             _head;
        point_t             _pill;
        int                 _dir;
        int                 _newdir;
        int                 _length;
        int                 _alength;
        int                 _score;
};

#endif
