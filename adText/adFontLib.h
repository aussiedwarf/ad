#ifndef FONTLIB_H
#define FONTLIB_H

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

#include <string>
#include <vector>

#include "adFont.h"

/// \brief handles fonts
class adFontLib
{
public:
  adFontLib();
  ~adFontLib();

  /// \brief loads font returning its index
  /// \param a_file font file to load
  /// \param a_size font size
  /// \return font handle
  int LoadFont(const char* a_file, int a_size);

  /// \brief Grabs a font based off its index
  /// \param a_index font handle
  /// \return font
  adFont* GetFont(int a_index);

  /// \brief Grabs font based off exact name and size
  /// \param a_index returns the index of the font
  /// \param a_name path to font
  /// \param a_size size of font
  /// \return font
  adFont* GetFont(int &a_index, std::string a_name, int a_size);

protected:
  std::vector<adFont*> m_font;
};

#endif
