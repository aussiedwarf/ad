#ifndef AD_IMAGE_H
#define AD_IMAGE_H

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



/// \brief Represents a loaded image
class adImage
{
public:

  /// \brief Loads a image into a SDL surface
  /// \param a_file path to file to load
	/// \return surface with loaded image
  static SDL_Surface* LoadImage(const char* a_file);

  /// \brief converts a SDL surface to a opengl texture
  /// \param a_surface surface to load
  /// \return texture handle
  static unsigned int MakeTexture(SDL_Surface *a_surface);

protected:

};



#endif
