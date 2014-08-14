#ifndef AD_TEXT_H
#define AD_TEXT_H

/*
Copyright (c) 2014 Eden Harris

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "../adPlatform/adPlatform.h"

#include <cstdarg>
#include <cstdio>
#include <string>
#include <cmath>


#include <SDL2/SDL.h>


#include <SDL_ttf.h>


#include "adFont.h"
#include "adTextShader.h"
#include "adImage.h"

/// \brief Holds text that can be displayed
class adText
{
public:

  enum Alignment
  {
    LEFT = 0,
    CENTRE,
    RIGHT
  };

  adText();
  adText(bool a_texture, adFont *a_font, unsigned int a_color, std::string a_text, ...);
  ~adText();

  /// \brief Creates a texture that OpenGL can use to display.
  void CreateTexture();
  void DestroyTexture();

  /// \brief Displays text through OpenGL methods.
  void Draw(int a_x, int a_y, Alignment a_align = LEFT, bool a_center_height = false);

  bool MakeText(adFont *a_font, unsigned int a_color, std::string a_text, ...);

  /// \brief Makes text.
  /// \param a_texture specify whether to automatically make text
  bool MakeText(bool a_texture, adFont *a_font, unsigned int a_color, std::string a_text, ...);
  bool MakeTextArgs(bool a_texture, adFont *a_font, unsigned int a_color, const char *a_fmt, va_list a_argp);

  SDL_Surface *m_surface;
  unsigned int m_texture;

  int m_width;
  int m_height;
  int m_textWidth;
  int m_textHeight;

  unsigned int m_color;

  std::string m_text;
  adFont *m_font;

  adTextShader *m_textShader;

protected:

  

  int NearestPowerOfTwo(int a_num);

};

#endif


