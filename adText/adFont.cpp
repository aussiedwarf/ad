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

#include "adFont.h"



adFont::adFont()
{
  m_font = NULL; 
  m_name = "";
  m_size = 0;
}


adFont::~adFont()
{
  TTF_CloseFont(m_font);
}


//Load Font
bool adFont::LoadFont(const char* a_file, int a_size)
{
  m_font = TTF_OpenFont(a_file, a_size);
  if (m_font == NULL)
  {
    return false;
  }
  else
  {
    m_name = a_file;
    m_size = a_size;
    return true;
  }
}

//Make Text
#if 0
Text* adFont::MakeText(unsigned int a_color, const char a_text[], ...)
{
  va_list		argument_pointer;					// Pointer To List Of Arguments
	char		text[256];				// Holds Our String


	va_start(argument_pointer, a_text);					// Parses The String For Variables
	vsprintf(text, a_text, argument_pointer);				// And Converts Symbols To Actual Numbers
	va_end(argument_pointer);						// Results Are Stored In Text

  //get color
  SDL_Color color = {(a_color & 0xff0000) >> 16, (a_color & 0xff00) >> 8, a_color & 0xff};

  Text *text_class = new Text;

  //create surface with text
  text_class->m_text = TTF_RenderText_Blended(m_font, text, color);

  return text_class;

}

#endif

std::string adFont::GetName()
{
  return m_name;
}

int adFont::GetSize()
{
  return m_size;
}

