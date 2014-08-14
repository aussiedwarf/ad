#ifndef AD_WINDOW_H
#define AD_WINDOW_H
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


#include <SDL2/SDL.h>


#include <glm/glm.hpp>


class adWindow
{
public:
  adWindow();
  adWindow(glm::ivec2 a_size);
  ~adWindow();

  bool CreateWindow(glm::ivec2 a_size);

  //Update the window when resized
  void UpdateSize(glm::ivec2 a_size);

  //Resize Window
  void Resize(glm::ivec2 a_size);

  
  glm::ivec2 m_size;
  glm::ivec2 m_minSize;
  glm::ivec2 m_maxSize;

  int m_bpp;

  bool m_fullScreen;
  bool m_resizable;

  SDL_Window* m_window;
  SDL_GLContext m_glContext;
protected:
  void InitSettings();

};

#endif  //AD_WINDOW_H

