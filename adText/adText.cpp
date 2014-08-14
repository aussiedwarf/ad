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

#include "adText.h"
#include "../adPlatform/adOpenGL.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

using namespace std;


adText::adText()
{
  m_surface = NULL;
  m_texture = 0;
  m_font = NULL;
  m_width = 0;
  m_height = 0;
  m_textWidth = 0;
  m_textHeight = 0;
  m_color = 0;
}

adText::adText(bool a_texture, adFont *a_font, unsigned int a_color, std::string a_text, ...)
{
  m_surface = NULL;
  m_texture = 0;
  m_font = NULL;
  m_width = 0;
  m_height = 0;
  m_textWidth = 0;
  m_textHeight = 0;
  m_color = 0;

  va_list argp;
	va_start(argp, a_text);

  MakeTextArgs(a_texture, a_font, a_color, a_text.c_str(), argp);

  va_end(argp);
}


adText::~adText()
{
  if(m_surface != NULL)
  {
    SDL_FreeSurface(m_surface);
  }

  DestroyTexture();

  m_texture = 0;

  m_width = 0;
  m_height = 0;
  m_textWidth = 0;
  m_textHeight = 0;

  m_color = 0;

  //m_text;
  //m_font;
}

bool adText::MakeTextArgs(bool a_texture, adFont *a_font, unsigned int a_color, const char *a_fmt, va_list a_argp)
{		
  char *text = new char[2048]; // Holds Our String


	vsprintf(text, a_fmt, a_argp);				// And Converts Symbols To Actual Numbers

  /// \to copy text(char) to m_text
  m_text = text;
  m_color = a_color;
  m_font = a_font;

  //get color
  SDL_Color color = {static_cast<unsigned char>((a_color & 0xff0000) >> 16), static_cast<unsigned char>((a_color & 0xff00) >> 8), static_cast<unsigned char>(a_color & 0xff)};


	//a_font->GetName();

  //create surface with text
  m_surface = TTF_RenderText_Blended(a_font->m_font, text, color);
  //m_surface = TTF_RenderText_Shaded(a_font->m_font, text, color, color2);
  if(! m_surface)
  {
    return false;
  }
  m_textWidth = m_surface->w;
  m_textHeight = m_surface->h;

  if(a_texture)
  {
    CreateTexture();
  }

  delete[] text;

  return true;
}

void adText::CreateTexture()
{
  //make sure we ado not already have a texture
  DestroyTexture();

  //to convert to textures we need the image to have a size to the power of to. eg 2,4,8,16,32,etc
  //some harware only support textures up to 2048x2048 so this may need to be modified to support multiple textures

  //There are a couple ways to get the closest power of 2. We could find the most significant bit in the size and if this is the only bit set
  //then we use this size. Otherwise we just shift the bit over. The most significant bit can be found by a long masking and searching function, 
  //or with _BitScanReverse on visual studio or __builtin_clz in gcc. Another way is to use logarithms.

  m_width = NearestPowerOfTwo(m_surface->w);
  m_height = NearestPowerOfTwo(m_surface->h);

  //this took some experimentation. I believe it changes on different systems. needs more research
  SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE, m_width, m_height, 32, //0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
			//0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

			//0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
			m_surface->format->Rmask, m_surface->format->Gmask, m_surface->format->Bmask, m_surface->format->Amask);


			//0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
			//0x00ff0000, 0x0000ff00, 0x000000ff, 0);

  // Save the alpha blending attributes
#if 0
  unsigned int saved_flags = m_surface->flags&(SDL_SRCALPHA);  //|SDL_RLEACCELOK
  //unsigned char saved_alpha = m_text->format->alpha;
  if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
      SDL_SetAlpha(m_surface, 0, 0);
  }
#endif

  // Copy the surface into the GL texture image

  SDL_Rect area;
  area.x = 0;
  area.y = 0;
  area.w = m_surface->w;
  area.h = m_surface->h;

	SDL_BlitSurface(m_surface, &area, surface, &area);

  m_texture = adImage::MakeTexture(surface);

  SDL_FreeSurface(surface);

}

void adText::DestroyTexture()
{
  if(m_texture)
  {
    glDeleteTextures(1, &m_texture);
  }
}

void adText::Draw(int a_x, int a_y, Alignment a_align, bool a_center_height)
{
  //if texture exists then draw
  if(m_texture)
  {
    float vertexCoords[8] =
    {
        0, 100,
        0, 0,
        100, 100,
        100, 0
    };

    float texCoords[] =
    {
    /*
        0.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 1.0
      */
      0.0, 1.0,
      1.0, 1.0,
      1.0, 0.0,
      0.0, 0.0
    };

    float y_top = 0.0f;
    float y_bottom = static_cast<float>(m_height);

    if(a_center_height)
    {
      y_top = static_cast<float>(-m_textHeight/2);
      y_bottom = static_cast<float>(m_height - m_textHeight/2);
    }

    if(a_align == RIGHT)
    {
      vertexCoords[0] = -m_textWidth;
      vertexCoords[1] = y_top;
      vertexCoords[2] = m_width - m_textWidth;
      vertexCoords[3] = y_top;
      vertexCoords[4] = m_width - m_textWidth;
      vertexCoords[5] = y_bottom;
      vertexCoords[6] = -m_textWidth;
      vertexCoords[7] = y_bottom;

    }
    else if(a_align == CENTRE)
    {
      vertexCoords[0] = -m_textWidth/2.0f;
      vertexCoords[1] = y_top;
      vertexCoords[2] = m_width - m_textWidth/2.0f;
      vertexCoords[3] = y_top;
      vertexCoords[4] = m_width - m_textWidth/2.0f;
      vertexCoords[5] = y_bottom;
      vertexCoords[6] = -m_textWidth/2.0f;
      vertexCoords[7] = y_bottom;

		}
		else
		{
			vertexCoords[0] = 0.0f;
			vertexCoords[1] = y_top;
			vertexCoords[2] = m_width;
			vertexCoords[3] = y_top;
			vertexCoords[4] = m_width;
			vertexCoords[5] = y_bottom;
			vertexCoords[6] = 0.0f;
			vertexCoords[7] = y_bottom;


		}


    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

    glm::mat4 mat(1.0f);
    glm::mat4 proj(1.0f);
    glm::mat4 modelView(1.0f);

    proj = glm::ortho(0.0f, (float)m_textShader->m_width,0.0f, (float)m_textShader->m_height, -1.0f, 1.0f);
    //mat =
    modelView = glm::translate(modelView, glm::vec3((float)a_x, (float)a_y, 0.0f));

    mat = proj * modelView;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_textShader->m_shaderProgram);

    glVertexAttribPointer( m_textShader->m_posLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), vertexCoords );
    glVertexAttribPointer( m_textShader->m_texLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), texCoords );

    glEnableVertexAttribArray( m_textShader->m_posLoc );
    glEnableVertexAttribArray( m_textShader->m_texLoc );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture );

    glUniform1i( m_textShader->m_samplerLoc, 0 );
    glUniformMatrix4fv(m_textShader->m_matLoc, 1, false, &mat[0][0]);

    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );

    glDisableVertexAttribArray( m_textShader->m_posLoc );
    glDisableVertexAttribArray( m_textShader->m_texLoc );


#if 0

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	  glBindTexture(GL_TEXTURE_2D, m_texture);

		glColor3f(1.0f, 1.0f, 1.0f);

    float y_top = 0.0f;
    float y_bottom = static_cast<float>(m_height);

    if(a_center_height)
    {
      y_top = static_cast<float>(-m_textHeight/2);
      y_bottom = static_cast<float>(m_height - m_textHeight/2);
    }

    if(a_align == RIGHT)
    {
      glBegin(GL_QUADS);
		    glTexCoord2f(0.0f, 1.0f);
				glVertex2f(static_cast<GLfloat>(-m_textWidth), y_top);

		    glTexCoord2f(1.0f, 1.0f);
				glVertex2f(static_cast<GLfloat>(m_width - m_textWidth), y_top);

		    glTexCoord2f(1.0f, 0.0f);
				glVertex2f(static_cast<GLfloat>(m_width - m_textWidth), y_bottom);

		    glTexCoord2f(0.0f, 0.0f);
				glVertex2f(static_cast<GLfloat>(-m_textWidth) , y_bottom);
	    glEnd();
    }
    else if(a_align == CENTRE)
    {
      glBegin(GL_QUADS);
		    glTexCoord2f(0.0f, 1.0f);
				glVertex2f(static_cast<GLfloat>(-m_textWidth/2.0f), y_top);

		    glTexCoord2f(1.0f, 1.0f);
				glVertex2f(static_cast<GLfloat>(m_width - m_textWidth/2.0f), y_top);

		    glTexCoord2f(1.0f, 0.0f);
				glVertex2f(static_cast<GLfloat>(m_width - m_textWidth/2.0f), y_bottom);

		    glTexCoord2f(0.0f, 0.0f);
				glVertex2f(static_cast<GLfloat>(-m_textWidth/2.0f) , y_bottom);
	    glEnd();
      
    }
    else  //LEFT
    {
      glBegin(GL_QUADS);
		    glTexCoord2f(0.0f, 1.0f);
			  glVertex2f(0.0f, y_top);

		    glTexCoord2f(1.0f, 1.0f);
			  glVertex2f(static_cast<GLfloat>(m_width), y_top);

		    glTexCoord2f(1.0f, 0.0f);
			  glVertex2f(static_cast<GLfloat>(m_width), y_bottom);

		    glTexCoord2f(0.0f, 0.0f);
			  glVertex2f(0.0f , y_bottom);
	    glEnd();
    }
	  

	  glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

#endif
  }
}

bool adText::MakeText(adFont *a_font, unsigned int a_color, std::string a_text, ...)
{
  va_list		argument_pointer;					// Pointer To List Of Arguments				
  char *text = new char[a_text.length()+1]; // Holds Our String

	va_start(argument_pointer, a_text);					// Parses The String For Variables
	vsprintf(text, a_text.c_str(), argument_pointer);				// And Converts Symbols To Actual Numbers
	va_end(argument_pointer);						// Results Are Stored In Text

  /// \to copy text(char) to m_text
  m_text = a_text;
  m_color = a_color;
  m_font = a_font;

  //get color
  SDL_Color color = {static_cast<unsigned char>((a_color & 0xff0000) >> 16), static_cast<unsigned char>((a_color & 0xff00) >> 8), static_cast<unsigned char>(a_color & 0xff)};

	//a_font->GetName();

  //create surface with text
  m_surface = TTF_RenderText_Blended(a_font->m_font, text, color);




  m_textWidth = m_surface->w;
  m_textHeight = m_surface->h;

  return true;
}

bool adText::MakeText(bool a_texture, adFont *a_font, unsigned int a_color, std::string a_text, ...)
{
  bool result = true;

  va_list argp;
	va_start(argp, a_text);

  result = MakeTextArgs(a_texture, a_font, a_color, a_text.c_str(), argp);

  va_end(argp);

  return result;
}

int adText::NearestPowerOfTwo(int a_num)
{
  //using log method since it works on all systems
  float logbase2 = log(static_cast<float>(a_num)) / log(2.0f);
	return static_cast<int>(pow(2,ceil(logbase2)) + 0.5f);
}


