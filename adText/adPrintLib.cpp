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
#include "../adPlatform/adOpenGL.h"
#include "adPrintLib.h"




#include <iostream>

adPrintLib::adPrintLib() : m_textShader(NULL)
{
  m_textShader = new adTextShader;
}

adPrintLib::~adPrintLib()
{
  delete m_textShader;
}

bool adPrintLib::Init(int a_w, int a_h)
{
  m_textShader->m_width = a_w;
  m_textShader->m_height = a_h;

  //load shaders
  const GLchar *vshader_source =
    #ifndef RASPI
      "#version 110                 \n"
    #endif
      "uniform mat4 u_MVPMatrix;    \n"
      "attribute vec4 a_position;   \n"
      "attribute vec2 a_texCoord;   \n"
      "varying vec2 v_texCoord;     \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = u_MVPMatrix * a_position; \n"
      "   v_texCoord = a_texCoord;  \n"
      "}                            \n";

  const GLchar *fshader_source =
    #ifndef RASPI
      "#version 110                   \n"
    #endif
      "varying vec2 v_texCoord;                            \n"
      "uniform sampler2D s_texture;                        \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
      "}                                                   \n";

  //compile shaders
  int shaderResult = 0;

  m_textShader->m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(m_textShader->m_vertexShader, 1, &vshader_source, 0);
  glCompileShader(m_textShader->m_vertexShader);
  glGetShaderiv(m_textShader->m_vertexShader, GL_COMPILE_STATUS, &shaderResult);
  if(!shaderResult)
  {
    std::cerr << "Error compiling printlib vertex shader" << std::endl;
    return false;
  }

  m_textShader->m_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(m_textShader->m_fragShader, 1, &fshader_source, 0);
  glCompileShader(m_textShader->m_fragShader);
  glGetShaderiv(m_textShader->m_fragShader, GL_COMPILE_STATUS, &shaderResult);
  if(!shaderResult)
  {
    std::cerr << "Error compiling printlib fragment shader" << std::endl;
    return false;
  }

  //create shader program

  m_textShader->m_shaderProgram = glCreateProgram();
  glAttachShader(m_textShader->m_shaderProgram, m_textShader->m_vertexShader);
  glAttachShader(m_textShader->m_shaderProgram, m_textShader->m_fragShader);
  glLinkProgram(m_textShader->m_shaderProgram);

  glGetProgramiv(m_textShader->m_shaderProgram,GL_LINK_STATUS,&shaderResult);
  if(!shaderResult)
  {
    std::cerr << "Error linking shaders" << std::endl;
    return false;
  }
  m_textShader->m_matLoc = glGetUniformLocation( m_textShader->m_shaderProgram, "u_MVPMatrix");
  m_textShader->m_posLoc = glGetAttribLocation ( m_textShader->m_shaderProgram, "a_position" );
  m_textShader->m_texLoc = glGetAttribLocation ( m_textShader->m_shaderProgram, "a_texCoord" );

  // Get the sampler location
  m_textShader->m_samplerLoc = glGetUniformLocation ( m_textShader->m_shaderProgram, "s_texture" );

  return true;
}

void adPrintLib::SetScreen(int a_w, int a_h)
{
  m_textShader->m_width = a_w;
  m_textShader->m_height = a_h;
}

void adPrintLib::Print(int a_x, int a_y, unsigned int a_color, adFont *a_font, int a_size, std::string a_string, ...)
{
  adTextPrint *print = new adTextPrint();
  print->m_textShader = m_textShader;
  char *text = new char[1024];

  //convert
  va_list argp;
	va_start(argp, a_string);

  vsprintf(text, a_string.c_str(), argp);

  va_end(argp);

  //search for text
  bool found = false;

  std::list<adTextPrint*>::iterator it = m_text.begin();
  std::list<adTextPrint*>::iterator current;
  
  while(it != m_text.end() && !found)
  {
    
    if( (*it)->m_font->GetSize() == a_size && (*it)->m_color == a_color && 
      (*it)->m_font->m_font == a_font->m_font && !strcmp(text, (*it)->m_text.c_str()) )
    {
      found = true;
      (*it)->m_frameHold = 2;
      current = it;
    }
    
    it++;
  }

  //std::cout << text << " " << found << " " << m_text.size() << std::endl;
  
  //if not found add to list
  if(!found)
  {
    print->MakeText(true, a_font, a_color, text);

    m_text.push_back(print);

    current = m_text.end();
    current--;
  }
  else 
  {
    delete print;
  }
  
  //draw
  (*current)->Draw(a_x, a_y);
  delete[] text;
  //delete print;
}

void adPrintLib::Print(int a_x, int a_y, unsigned int a_color, adFont *a_font, int a_size,
    adText::Alignment a_align, bool a_center_height, std::string a_string, ...)
{
  adTextPrint *print = new adTextPrint();
  print->m_textShader = m_textShader;
  char *text = new char[1024];

  //convert
  va_list argp;
	va_start(argp, a_string);

  vsprintf(text, a_string.c_str(), argp);

  va_end(argp);

  //search for text
  bool found = false;

  std::list<adTextPrint*>::iterator it = m_text.begin();
  std::list<adTextPrint*>::iterator current;
  
  while(it != m_text.end() && !found)
  {
    
    if( (*it)->m_font->GetSize() == a_size && (*it)->m_color == a_color && 
      (*it)->m_font->m_font == a_font->m_font && !strcmp(text, (*it)->m_text.c_str()) )
    {
      found = true;
      (*it)->m_frameHold = 2;
      current = it;
    }
    
    it++;
  }
  
  //if not found add to list
  if(!found)
  {
    print->MakeText(true, a_font, a_color, text);

    m_text.push_back(print);

    current = m_text.end();
    current--;
  }
  else 
  {
    delete print;
  }

  
  //draw
  (*current)->Draw(a_x, a_y, a_align, a_center_height);
  delete[] text;
}

void adPrintLib::Update()
{
  std::list<adTextPrint*>::iterator it = m_text.begin();

  //loop through text
  while(it != m_text.end())
  {
    (*it)->m_frameHold--;

    //if time to remove then remove
    if( (*it)->m_frameHold <= 0)
    {
      delete (*it);
      m_text.erase(it++);
    }
    else
    {
      it++;
    }
  }
}

adPrintLib::adTextPrint::adTextPrint()
{
  m_frameHold = 2;
}

adPrintLib::adTextPrint::~adTextPrint()
{
  m_frameHold = 0;
}
