#ifndef AD_VIEW_H
#define AD_VIEW_H

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

#include <glm/glm.hpp>

class adView
{
public:
  enum MoveMask {
    MaskNone              = 0x000000,
    MaskForwards          = 0x000001,
    MaskBackwards         = 0x000002,
    MaskLeft              = 0x000004,
    MaskRight             = 0x000008,
    MaskUp                = 0x000010,
    MaskDown              = 0x000020,
    MaskYawLeft           = 0x000040,
    MaskYawRight          = 0x000080,
    MaskPitchUp           = 0x000100,
    MaskPitchDown         = 0x000200,
    MaskRollAntiCLockwise = 0x000400,
    MaskRollClockwise     = 0x000800,
    MaskOrbitLeft         = 0x001000,
    MaskOrbitRight        = 0x002000,
    MaskOrbitUp           = 0x004000,
    MaskOrbitDown         = 0x008000,
    MaskOrbitIn           = 0x010000,
    MaskOrbitOut          = 0x020000
  };

  enum Move {
    Forwards          = 0,
    Backwards         = 1,
    Left              = 2,
    Right             = 3,
    Up                = 4,
    Down              = 5,
    YawLeft           = 6,
    YawRight          = 7,
    PitchUp           = 8,
    PitchDown         = 9,
    RollAntiCLockwise = 10,
    RollClockwise     = 11,
    OrbitLeft         = 12,
    OrbitRight        = 13,
    OrbitUp           = 14,
    OrbitDown         = 15,
    OrbitIn           = 16,
    OrbitOut          = 17,
    Count             = 18
  };

	glm::mat4x4 m_matrixViewport;
	glm::mat4x4 m_matrixProjection;
	glm::mat4x4 m_matrixView;
	glm::mat4x4 m_matrixCamera;

  glm::dmat4x4 m_dmatrixViewport;
  glm::dmat4x4 m_dmatrixProjection;
  glm::dmat4x4 m_dmatrixView;
  glm::dmat4x4 m_dmatrixCamera;

  glm::ivec2 m_viewSize;
  glm::ivec2 m_viewPosition;

  glm::vec3 m_cameraPosition;
  glm::vec3 m_cameraEuler;
  glm::vec3 m_cameraZoom;
  glm::vec3 m_cameraTarget;

  glm::dvec3 m_dcameraPosition;
  glm::dvec3 m_dcameraEuler;
  glm::dvec3 m_dcameraZoom;
  glm::dvec3 m_dcameraTarget;

  glm::vec3 m_up;
  glm::dvec3 m_dup;

  //allows roll to be introduced from yaw, pitch rotations. Can still explicitly roll
  bool m_allowRoll;

  adView();
  ~adView(){};

  void TranslateView(const glm::vec3 a_v);
  void TranslateView(const glm::dvec3 a_v);

  void RotateView(const glm::vec3 a_v);
  void RotateView(const glm::dvec3 a_v);

  void MoveView(const float a_move[]);
  void MoveView(const double a_move[]);

  void SetPosition(const glm::vec3 a_v);
  void SetPosition(const glm::dvec3 a_v);

  void SetAngle(const glm::vec3 a_v);
  void SetAngle(const glm::dvec3 a_v);

  glm::vec3 GetPosition() const;
  glm::dvec3 GetPositionD() const;

  glm::vec3 GetEuler() const;
  glm::dvec3 GetEulerD() const;

  //will useually calculate camera matrix from view matrix
  glm::mat4x4 GetCameraMatrix();
  glm::dmat4x4 GetCameraMatrixD();

  //update double/float data from each other
  void UpdateDoubles();
  void UpdateFloats();

};



#endif //AD_VIEW_H
