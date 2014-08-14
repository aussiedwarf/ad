#ifndef AD_FONT_H
#define AD_FONT_H

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


#include <cstdarg>
#include <cstdio>
#include <string>

#include "../adPlatform/adPlatform.h"


#include <SDL_ttf.h>

//#include "Text.h"

/// \brief contains font information
class adFont
{
public:
  adFont();
  ~adFont();

  /// \brief Load Font
  /// \param a_file path to font file
  /// \param a_size font size
  /// \return load success
  bool LoadFont(const char* a_file, int a_size);

  /// \brief Make Text
  //Text* MakeText(unsigned int a_color, const char a_text[], ...);

  /// \brief Gets the name of the font
  /// \return font name
  std::string GetName();

  /// \brief returns the size of the font
  /// \return font size
  int GetSize();

  //MakeText(0xffffffff, "this is text %i %u", inte, dgedg);

  

  TTF_Font *m_font;

protected:
  std::string m_name;
  int m_size;

  

};

#endif

