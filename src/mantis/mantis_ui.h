/*==============================================================================
 * Mantis Engine user interface class headers
 *==============================================================================
 * Copyright (C) 2017 Duncan Tilley <duncan.tilley@gmail.com>
 *
 * This file is part of Mantis Engine.
 *
 * Mantis Engine is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Mantis Engine is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Mantis Engine.  If not, see <http://www.gnu.org/licenses/>.
 *============================================================================*/

#ifndef ME_UI_H
#define ME_UI_H

#include <string>
#include <vector>

// forward declarations
class ME_UiObserver;
class ME_UiComponent;
class ME_Button;

// observer list typedef
typedef std::vector<ME_UiObserver*> uiobslist_t;

#include "mantis.h"

/*==============================================================================
 * ME_UiObserver
 *
 *     Interface used by UI components to provide the callback
 *     uiActionPerformed() function.
 *============================================================================*/
class ME_UiObserver
{
    public:
        virtual void uiActionPerformed() = 0;
};

/*==============================================================================
 * ME_UiComponent
 *
 *     The superclass to all UI components that contains a few universally
 *     applied methods and attributes. UI Components are special entities that
 *     can be added to a stage that reacts to user input.
 *============================================================================*/
class ME_UiComponent : public ME_Entity
{
    public:
        ME_UiComponent();
        virtual ~ME_UiComponent();

        /*----------------------------------------------------------------------
         * Override from ME_Entity.                                           */
        virtual void update(double);
        virtual void render(ME_Graphics*);

        /*----------------------------------------------------------------------
         * Universal UI methods.                                              */
        void requestFocus();
        bool isFocused();
        void setHover(bool);
        bool isHovered();
        /* Position and bounds related methods.                               */
        virtual void setSize(int w, int h);
        virtual void setPosition(int x, int y);
        virtual void setBounds(int x, int y, int w, int h);
        virtual void setBounds(const ME_Rectangle*);
        virtual void setCenterPosition(int x, int y);
        /* Action observer methods.                                           */
        void addUiObserver(ME_UiObserver*);

    protected:
        /*----------------------------------------------------------------------
         * Notify all the observers.                                          */
        void performAction();

    private:
        bool         _focused;
        bool         _hovered;
        ME_Rectangle _bounds;
        uiobslist_t  _observers;
};

/*==============================================================================
 * ME_Button
 *
 *     A simple GUI button component that contains a bounding box, a label
 *     and responds to user click events.
 *============================================================================*/
class ME_Button : public ME_UiComponent
{
    public:
        ME_Button(std::string label);
        ~ME_Button();

        /*----------------------------------------------------------------------
         * Override from ME_UiComponent.                                      */
        virtual void render(ME_Graphics*);

    private:
        std::string _label;
};

#endif
