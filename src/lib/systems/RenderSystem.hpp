#pragma once

#include "LittleOBJLoader.h"
#include "core/System.hpp"

class Event;

class RenderSystem : public System {
 public:
  void drawSkybox();

  void Init();

  void Update();

 private:
  Entity mCamera;
  mat4 cameraMatrix;
  mat4 projectionMatrix;
  Model *skyboxModel;
  GLuint noShadeProgram;
  vec3 groundBallPos = vec3(0, 0, 0);
};
