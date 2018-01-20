/*==============================================================================
 * Mantis Engine graphics class headers
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

#ifndef ME_GRAPHICS_H
#define ME_GRAPHICS_H

/*==============================================================================
 * ME_Color
 *
 *     Represents an ARGB color.
 *============================================================================*/
class ME_Color
{
    public:
        ME_Color(int a = 0xff, int r = 0xff, int g = 0xff, int b = 0xff);
        ME_Color(int r, int g, int b);
        ME_Color(int a, int rgb);
        ME_Color(int rgb);
        ME_Color(const ME_Color&);
        ~ME_Color();

        ME_Color& operator=(const ME_Color&);

        /*----------------------------------------------------------------------
         * Accessors.                                                         */
        int getAlpha() const;
        int getRed() const;
        int getGreen() const;
        int getBlue() const;

        /*----------------------------------------------------------------------
         * Mutators.                                                          */
        void setAlpha(int);
        void setRed(int);
        void setGreen(int);
        void setBlue(int);
        void setColor(ME_Color*);
        void setColor(int a, int r, int g, int b);
        void setColor(int r, int g, int b);
        void setColor(int a, int rgb);
        void setColor(int rgb);

        SDL_Color* getSDLColor();
    private:
        SDL_Color* _color;
};

/*==============================================================================
 * ME_Graphics
 *
 *     Represents a rendering device that is associated with the window. This
 *     device is passed to all rendering functions and is used for the creation
 *     of images.
 *============================================================================*/
class ME_Graphics
{
	public:
		~ME_Graphics();

		/*----------------------------------------------------------------------
		 * Clear the rendering canvas to the current color                    */
		void clear();

		/*----------------------------------------------------------------------
		 * Color management functions                                         */
        void setColor(ME_Color*);
		void setColor(int r, int g, int b);
 		void setColor(int a, int r, int g, int b);
        void setColor(int a, int rgb);
        void setColor(int rgb);

		/*----------------------------------------------------------------------
		 * Rendering quality functions                                        */
		void setTextureFiltering(bool);
		void setSmoothFonts(bool);

		/*----------------------------------------------------------------------
		 * Image rendering functions                                          */
		void drawImage(ME_Image*);
		void drawImage(ME_Image*, int x, int y);
		void drawImage(ME_Image*, int x, int y, int w, int h);

		/*----------------------------------------------------------------------
		 * Geometry rendering functions                                       */
		void drawRect(const ME_Rectangle*);
		void drawRect(int x, int y, int w, int h);
		void fillRect(const ME_Rectangle*);
		void fillRect(int x, int y, int w, int h);
		void drawLine(int x1, int y1, int x2, int y2);

		/*----------------------------------------------------------------------
		 * Text rendering functions                                           */
		void setFont(std::string, int);
		void drawText(int x, int y, std::string);
		void drawText(int x, int y, std::string, ME_Rectangle* clip);
		/* These return the dimensions of text if it is rendered using the
		 * current set font.                                                  */
		int getTextHeight(std::string);
		int getTextWidth(std::string);

		/*----------------------------------------------------------------------
		 * SDL renderer access                                                */
		SDL_Renderer* getSDLRenderer();
		void recreateSDLRenderer(ME_Window*, bool vsync);

	private:
		/*----------------------------------------------------------------------
		 * Only the window is allowed to create rendering devices.            */
		friend class ME_Window;
		ME_Graphics(ME_Window*);
		SDL_Renderer* _renderer;
		ME_Color      _color;
		TTF_Font*     _font;
		bool          _smoothfont;
		bool          _texturefilt;
};

#endif
