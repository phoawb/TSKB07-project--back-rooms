#pragma once

#include "LittleOBJLoader.h"
#include "ShaderManager.hpp"
#include "LightManager.hpp"
#include "core/System.hpp"

class Event;

class RenderSystem : public System {
 public:
  void drawSkybox();

  void drawGroundSphere();

  void Init();

  void Update();

 private:
  Entity mCamera;
  mat4 cameraMatrix;
  mat4 projectionMatrix;
  LightManager lightManager;
  ShaderManager shaderManager;
  Model *groundSphereModel, *skyboxModel, *groundModel;
  GLuint terrainProgram, noShadeProgram;
  GLuint backroomsWallTex, backroomsFloorTex, skyboxTex, grassTex;
  vec3 groundBallPos = vec3(0, 0, 0);
};
