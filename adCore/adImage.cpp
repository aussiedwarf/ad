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

#include "adImage.h"
#include "../adPlatform/adOpenGL.h"
#include <SDL_image.h>

SDL_Surface* adImage::LoadImage(const char* a_file)
{
  SDL_Surface *surface;

  surface = IMG_Load(a_file);

  return surface;
}


unsigned int adImage::MakeTexture(SDL_Surface *a_surface)
{
  unsigned int texture;
  unsigned int format = 0;

  unsigned int *image = NULL;
  //unsigned int *pixels = NULL;
  bool delete_image = false;

  if(!a_surface)
  {
    return 0;
  }

  SDL_LockSurface(a_surface);
  image = static_cast<unsigned int*>(a_surface->pixels);

  //for SDL 1.3/2.0
#if 0
  //need to check the format of the surface
  switch(a_surface->format->format)
  {
  case SDL_PIXELFORMAT_RGB24:
    format = GL_RGB;
    break;

  //THis one works for bmp
  case SDL_PIXELFORMAT_BGR24:
    format = GL_BGR;
    break;
  
  case SDL_PIXELFORMAT_RGB888:
    format = GL_RGB;
    break;

  case SDL_PIXELFORMAT_RGBA8888:
    format = GL_RGBA;
    break;

  //this one works for tga
  case SDL_PIXELFORMAT_ARGB8888:
    format = GL_BGRA; 
    break;

  case SDL_PIXELFORMAT_BGR888:
    format = GL_BGR;
    break;

  case SDL_PIXELFORMAT_BGRA8888:
    format = GL_BGRA;
    break;

  case SDL_PIXELFORMAT_ABGR8888:
    format = GL_RGBA;
    break;

  }
#else
  format = GL_RGBA;
#endif

  //create a texture
  glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

  //load surface into texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, a_surface->w, a_surface->h, 0, format, GL_UNSIGNED_BYTE, image );
  //gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, a_surface->w, a_surface->h, format, GL_UNSIGNED_BYTE, image );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  SDL_UnlockSurface(a_surface);

  if(delete_image)
  {
    delete[] image;
  }

  return texture;
}

