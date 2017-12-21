/*==============================================================================
 * Mantis Engine global header file (include only this header)
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

#ifndef ME_MANTIS_H
#define ME_MANTIS_H

// external includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// forward declarations across all headers
class ME_Framework;
class ME_Graphics;
class ME_Window;
class ME_Exception;
class ME_Image;
class ME_ImageSheet;
class ME_Loop;
class ME_IntervalLoop;
class ME_UncappedLoop;
class ME_LoopObserver;
class ME_Entity;
class ME_Stage;
class ME_Thread;
class ME_Threadable;
class ME_UiObserver;
class ME_UiComponent;
class ME_Button;

// math forward declarations
class ME_Rectangle;

// all header includes
#include "math/mantis_math.h"
#include "mantis_exception.h"
#include "mantis_loop.h"
#include "mantis_main.h"
#include "mantis_image.h"
#include "mantis_stage.h"
#include "mantis_thread.h"
#include "mantis_ui.h"

#endif
