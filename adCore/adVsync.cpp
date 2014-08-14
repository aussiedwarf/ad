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

#include "adVsync.h"

#include <cstring>
#include <cstdio>

#include "../adPlatform/adPlatform.h"

#ifdef AD_LINUX
#ifdef AD_X86
#include <GL/glew.h>
#include <GL/glxew.h>

#include <GL/glx.h>
#endif
#endif


void SetVsyncHack(int a_v)
{
#ifdef AD_LINUX
#ifdef AD_X86
#if 0
  //typedef bool (APIENTRY *PFNWGLSWAPINTERVALFARPROC)(int);
  //typedef bool (APIENTRY * glSwapIntervalGlxExtFunc)(int);
  //PFNWGLSWAPINTERVALFARPROC glXSwapIntervalSGI = 0;

  glSwapIntervalGlxExtFunc glSwapIntervalFunc = NULL


  const unsigned char *extensions = glGetString( GL_EXTENSIONS );

  if( strstr( extensions, "glXSwapIntervalSGI" ) == 0 )
    return ; // Error: WGL_EXT_swap_control extension not supported on your computer.\n");
  else
  {
    glXSwapIntervalSGI = (PFNWGLSWAPINTERVALFARPROC)glXGetProcAddress( "GLX_EXT_swap_control" );

    if( glXSwapIntervalSGI )
      glXSwapIntervalSGI(a_v);
  }
#endif

  if ( glxewIsSupported ("GLX_SGI_swap_control") )
  {
    //cout << "GLX_SGI_swap_control" << endl;
    glXSwapIntervalSGI(a_v);

  }

  if(glxewIsSupported ("GLX_EXT_swap_control"))
  {
    //cout << "GLX_EXT_swap_control" << endl;
    //glXSwapIntervalEXT(a_v);
  }

  else
  {
    fprintf(stderr, "No extensions\n");
  }

#endif
#endif
}
