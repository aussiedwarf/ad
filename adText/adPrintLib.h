#ifndef PRINTLIB_H
#define PRINTLIB_H

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

#include <list>

#include "adText.h"
//#include "FontLib.h"
#include "adFont.h"
#include "adTextShader.h"

/// \brief A simple class that allows for displaying of text. Memory is managed.
/**
When Print is called, the class searches to see if the text has already been displayed. 
If it has not been displayed then it loads the text otherwise it uses the already loaded text. 
*/
class adPrintLib
{
public:

  adPrintLib();
  ~adPrintLib();

  //inits text shader
  bool Init(int a_w, int a_h);
  void SetScreen(int a_w, int a_h);

  void Print(int a_x, int a_y, unsigned int a_color, adFont *a_font, int a_size, std::string a_string, ...);
  void Print(int a_x, int a_y, unsigned int a_color, adFont *a_font, int a_size,
    adText::Alignment a_align, bool a_center_height, std::string a_string, ...);

  ///brief Checks to see if text should be unloaded.
  void Update();

protected:

  class adTextPrint: public adText
  {
  public:
    adTextPrint();
    ~adTextPrint();
    int m_frameHold;   /// The number of frames to hold for;
  };

  adTextShader *m_textShader;

  std::list<adTextPrint*> m_text;



};

#endif
