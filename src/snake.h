/*==============================================================================
 * Demo Program. This is the snake game stage and entity classes.
 *============================================================================*/

#ifndef DEMO_SNAKE_H
#define DEMO_SNAKE_H

#include "mantis/mantis.h"
#include <deque>

// window size of 720x720 allows 24px 30x30 grid
#define TILE_SIZE 24
#define FIELD_SIZE 30
#define START_LENGTH 5

#define DIR_RIGHT 3
#define DIR_LEFT  1
#define DIR_UP    0
#define DIR_DOWN  2

struct point_t
{
    int x;
    int y;
};

class Snake : public ME_Entity
{
    public:
        Snake();

        /*----------------------------------------------------------------------
         * Override from ME_Entity.                                           */
        void update(double);
        void render(ME_Graphics*);

        /*----------------------------------------------------------------------
         * Utility functions.                                                 */
        bool touchBody(const point_t&) const;
        bool touchHead(const point_t&) const;
        bool gameOver() const;
        void setDirection(int);
        void increaseLength();

    private:
        std::deque<point_t> _body;
        point_t             _head;
        int                 _dir;
        int                 _newdir;
        int                 _length;
        int                 _alength;
};

class SnakeStage : public ME_Stage
{
    public:
        SnakeStage(ME_Framework*);

        /*----------------------------------------------------------------------
         * Override from ME_Stage                                             */
        void update(double);
        void render(ME_Graphics*);
        void allocateResources(ME_Graphics*);
        void deallocateResources();

        /*----------------------------------------------------------------------
         * Event polling functions                                            */
        void onKeyPress(SDL_KeyboardEvent*);
    private:
        // pill placement
        void placePill();

        // variables
        Snake*  _snake;
        int     _width;
        int     _height;
        bool    _gameover;
        point_t _pill;
        int     _score;
        double  _time;
        double  _tick;
};

class PauseStage : public ME_Stage
{
    public:
        PauseStage(ME_Framework*);

        /*----------------------------------------------------------------------
         * Override from ME_Stage                                             */
        void update(double);
        void render(ME_Graphics*);
        void allocateResources(ME_Graphics*);
        void deallocateResources();

        /*----------------------------------------------------------------------
         * Event polling functions                                            */
        void onKeyPress(SDL_KeyboardEvent*);

    private:
        int _width;
        int _height;
};

#endif
