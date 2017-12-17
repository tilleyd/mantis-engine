/*==============================================================================
 * Mantis Engine stage class headers
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

#ifndef ME_STAGE_H
#define ME_STAGE_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

// forward declarations
class ME_Entity;
class ME_Stage;

// entity list typedef
typedef std::map<std::string, ME_Entity*> entitymap_t;

#include "mantis.h"

/*==============================================================================
 * ME_Stage
 *
 *     Represents a room or area in the game. Stages are the main method of
 *     organizing the game logic. The framework works on one stage at a time and
 *     each stage contains has the update() and render() methods, which are
 *     called by the framework to render or progress the stage. Entities can
 *     also be added as a more structured and automatic way of handling the
 *     update and rendering of entities in the stage.
 *============================================================================*/
class ME_Stage
{
	public:
		ME_Stage(ME_Framework*);
		virtual ~ME_Stage();

		/*----------------------------------------------------------------------
		 * Essential game loop functions.                                     */
		virtual void update(double) = 0;
		virtual void render(ME_Graphics*) = 0;
        /* These functions should be called in update() and render() if you make
         * use of entities.                                                   */
        virtual void updateEntities(double);
        virtual void renderEntities(ME_Graphics*);

		/*----------------------------------------------------------------------
		 * Essential resource functions (esp. image allocation).              */
		virtual void allocateResources(ME_Graphics*) = 0;
		virtual void deallocateResources() = 0;

        /*----------------------------------------------------------------------
         * Entity management functions. Each entity is associated with a tag
         * used for access to the entity.                                     */
        void addEntity(ME_Entity*, std::string tag);
        void removeEntity(std::string tag);
        ME_Entity* getEntity(std::string tag);

		/*----------------------------------------------------------------------
		 * Stage event triggered functions.                                   */
		virtual void onActivate() {}
		virtual void onDeactivate() {}

		/*----------------------------------------------------------------------
		 * Mouse event triggered functions.                                   */
		virtual void onMouseMotion(SDL_MouseMotionEvent*) {}
		virtual void onMousePress(SDL_MouseButtonEvent*) {}
		virtual void onMouseRelease(SDL_MouseButtonEvent*) {}
		virtual void onMouseWheel(SDL_MouseWheelEvent*) {}

		/*----------------------------------------------------------------------
		 * Keyboard event triggered functions.                                */
		virtual void onKeyPress(SDL_KeyboardEvent*) {}
		virtual void onKeyRelease(SDL_KeyboardEvent*) {}

		/*----------------------------------------------------------------------
		 * Window event triggered functions.                                  */
		virtual void onWindowChange(SDL_WindowEvent*) {}

	protected:
		ME_Framework* _framework;
        entitymap_t   _entities;
};

/*==============================================================================
 * ME_Entity
 *
 *     Entities are interactive (or possibly static) objects in the stage that
 *     can interact with each other, are updated and are rendered to the
 *     screen.
 *============================================================================*/
class ME_Entity
{
    public:
        virtual ~ME_Entity() {}

        /*----------------------------------------------------------------------
         * Essential game loop functions.                                     */
        virtual void update(double) = 0;
        virtual void render(ME_Graphics*) = 0;

    protected:
        friend class ME_Stage;
        ME_Stage*     _stage;
        ME_Framework* _framework;
};

#endif
