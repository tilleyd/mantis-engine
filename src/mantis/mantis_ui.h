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

// observer list typedef
typedef std::vector<ME_UiObserver*> uiobslist_t;

// ui action types
#define UI_MOUSE_PRESSED 0
#define UI_KEY_PRESSED   1

/*==============================================================================
 * ME_UiObserver
 *
 *     Interface used by UI components to provide the callback
 *     uiActionPerformed() function.
 *============================================================================*/
class ME_UiObserver
{
    public:
        virtual void uiActionPerformed(ME_UiComponent*, int action) = 0;
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
        bool isFocused() const;
        void setHovered(bool);
        bool isHovered() const;
        void setEnabled(bool);
        bool isEnabled() const;
        /* Position and bounds related methods.                               */
        virtual void setSize(int w, int h);
        virtual void setPosition(int x, int y);
        virtual void setBounds(const ME_Rectangle*);
        virtual void setBounds(int x, int y, int w, int h);
        virtual void setCenterPosition(int x, int y);
        virtual bool containsPoint(int x, int y) const;
        const ME_Rectangle* getBounds() const;
        /* Action observer methods.                                           */
        void addUiObserver(ME_UiObserver*);
        /* Notify all the observers.                                          */
        void performAction(int action);

    protected:
        ME_Rectangle _bounds;

    private:
        bool         _focused;
        bool         _hovered;
        bool         _enabled;
        uiobslist_t  _observers;
};

/*==============================================================================
 * ME_UiButton
 *
 *     A simple GUI button component that contains a bounding box, a label
 *     and responds to user click events.
 *============================================================================*/
class ME_UiButton : public ME_UiComponent
{
    public:
        ME_UiButton(std::string);
        virtual ~ME_UiButton();

        /*----------------------------------------------------------------------
         * Override from ME_UiComponent.                                      */
        virtual void render(ME_Graphics*);

        /*----------------------------------------------------------------------
         * Update the padding and size of the button according to the font.   */
        void adjustSizeToFont(ME_Graphics*);
        void setPadding(int hpad, int vpad);

    private:
        void getLabelMetrics(ME_Graphics*);
        std::string _label;
        int         _hpad, _vpad;
        int         _labelw, _labelh;
};

#endif
