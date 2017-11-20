/*==============================================================================
 * Demo Program. This is the menu stage class.
 *============================================================================*/

#ifndef DEMO_MENU_H
#define DEMO_MENU_H

#include "mantis/mantis.h"

class Menu : public ME_Stage
{
    public:
        Menu(ME_Framework*);

        /*----------------------------------------------------------------------
         * Override from ME_Stage                                             */
        void update(double);
        void render(ME_Graphics*);
    private:
        ME_Image* _mantis;
        int       _width;
        int       _height;

        // variables
        int       _imgx;
        int       _imgy;
        int       _xspeed;
        int       _yspeed;
};

#endif
