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

#include "adFontLib.h"




adFontLib::adFontLib()
{
  


}

adFontLib::~adFontLib()
{
  //using unsigned to stop warning
  for(unsigned int i = 0; i < m_font.size(); i++)
  {
    delete m_font[i];
  }
}

int adFontLib::LoadFont(const char* a_file, int a_size)
{
  adFont* font = new adFont;

  font->LoadFont(a_file, a_size);

  m_font.push_back(font);

  /// \todo check for vector.last
  return m_font.size()-1;
}

/// \todo bounds check
adFont* adFontLib::GetFont(int a_index)
{
  return m_font[a_index];
}

adFont* adFontLib::GetFont(int &index, std::string name, int size){
	int i = 0;
  std::vector<adFont*>::iterator fntIt = m_font.begin();
	while(fntIt != m_font.end()){
		if((*fntIt)->GetName() == name && (*fntIt)->GetSize() == size){
			index = i;
			return (*fntIt);
		}
		fntIt++;
		i++;
	}
	index = -1;
	return NULL;
}

