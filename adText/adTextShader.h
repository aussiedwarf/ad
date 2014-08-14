#ifndef AD_TEXTSHADER_H
#define AD_TEXTSHADER_H

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

struct adTextShader{

  unsigned int m_shaderProgram;
  unsigned int m_vertexShader;
  unsigned int m_fragShader;

  unsigned int m_posLoc;
  unsigned int m_texLoc;
  unsigned int m_matLoc;

  unsigned int m_samplerLoc;

  int m_width;
  int m_height;

};

#endif //AD_TEXTSHADER_H
