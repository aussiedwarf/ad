
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

#include "adView.h"

adView::adView()
{

  m_allowRoll = true;
}

void adView::TranslateView(const glm::vec3 a_v)
{

}

void adView::RotateView(const glm::vec3 a_v)
{

}

void adView::MoveView(const float a_move[])
{

}

void adView::SetPosition(const glm::vec3 a_v)
{
  m_cameraPosition = a_v;
  m_matrixView[3] = glm::vec4(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z, 1.f);
}

void adView::SetAngle(const glm::vec3 a_v)
{

}

glm::vec3 adView::GetPosition() const
{
  return m_cameraPosition;
}

glm::dvec3 adView::GetEulerD() const
{
  return m_dcameraEuler;
}

glm::mat4x4 adView::GetCameraMatrix()
{
  m_matrixCamera = glm::inverse(m_matrixView);
  return m_matrixCamera;

}
