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

#include "adWindow.h"
#include <cstdio>


adWindow::adWindow() : m_bpp(0), m_fullScreen(false), m_window(nullptr)
{
	InitSettings();
}

adWindow::adWindow(glm::ivec2 a_size) : m_bpp(0), m_fullScreen(false), m_window(nullptr)
{
  InitSettings();
  bool result = CreateWindow(a_size);
}

adWindow::~adWindow()
{
  SDL_GL_DeleteContext(m_glContext);

  if(m_window)
    SDL_DestroyWindow(m_window);

  m_window = nullptr;
}


void adWindow::InitSettings()
{
	m_size = glm::ivec2(100,100);
	m_bpp = 32;
	m_minSize = glm::ivec2(1,1);
	m_maxSize = glm::ivec2(0x7fffffff,0x7fffffff);
}

bool adWindow::CreateWindow(glm::ivec2 a_size)
{
  m_size = a_size;
	
  m_bpp = 32;


  // Initialize the SDL library with Video/Audio and timer support
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS))
  {
  	fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
    return false;
  }

  int sdlResult = 0;

  sdlResult = SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, m_bpp);
  if(sdlResult)
  {
    fprintf(stderr, "could not set attribute buffer size\n");
    return false;
  }

  //using a double buffer
  sdlResult =  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  if(sdlResult)
  {
   fprintf(stderr, "could not set attribute double buffer\n");
   return false;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Set the window mode
  Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE; //SDL_GL_DOUBLEBUFFER;  SDL_DOUBLEBUF |

  m_window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, a_size.x, a_size.y, flags);
  if (!m_window)
  {
      fprintf(stderr, "SDL: could not create window \n");
      return false;
  }

  m_glContext = SDL_GL_CreateContext(m_window);
  if (!m_glContext)
  {
      fprintf(stderr, "SDL: could not create context \n");
      return false;
  }

  if(SDL_GL_MakeCurrent(m_window, m_glContext))
  {
    fprintf(stderr, "SDL: could not set window context \n");
    return false;

  }

#if AD_WINDOWS
  GLenum err = glewInit();
  if(GLEW_OK != err)
  {
     fprintf(stderr, "Glew Error\n");
     fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
     return false;
  }
#endif

  return true;
}

void adWindow::UpdateSize(glm::ivec2 a_size)
{
  bool resize = false;

  if(a_size.x < m_minSize.x)
    resize = true;
  if(a_size.y < m_minSize.y)
    resize = true;
  glm::max(a_size, m_minSize);

  if(a_size.x > m_maxSize.x)
    resize = true;
  if(a_size.y > m_maxSize.y)
    resize = true;
  glm::min(a_size, m_maxSize);

  if(resize)
    Resize(a_size);

  m_size = a_size;
}


void adWindow::Resize(glm::ivec2 a_size)
{
  glm::max(a_size, m_minSize);
  glm::min(a_size, m_maxSize);
  m_size = a_size;

  SDL_SetWindowSize(m_window, a_size.x, a_size.y);
}
