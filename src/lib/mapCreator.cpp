#include "mapCreator.h"

#include <memory>
#include <queue>
#include <vector>

#include "LittleOBJLoader.h"
#include "VectorUtils4.h"
#include "algorithm"
#include "boxes.h"
#include "components/AABB.hpp"
#include "components/Renderable.hpp"
#include "components/RigidBody.hpp"
#include "components/Transform.hpp"
#include "core/Coordinator.hpp"
#include "mapGeneration/BinarySpacePartitioner.h"
#include "mapGeneration/mapGenerator.h"
#include "mapGeneration/mapUtils.h"
#include "mapGeneration/roomCreator.h"
#include "mapGeneration/roomGenerator.h"
#include "random"
#include "stdio.h"

extern Coordinator gCoordinator;

void MapCreator::start() { createMap(); }

void MapCreator::createMap() {
  MapGenerator mapGenerator(mapWidth, mapHeight);
  std::vector<NodePtr> map = mapGenerator.calculateMap(maxIterations, minRoomWidth, minRoomHeight);
  RoomCreator roomCreator = RoomCreator();
  for (NodePtr biome : map) {
    // createFloorModel(biome->bottomLeftCorner, biome->getWidth(), biome->getHeight());
    roomCreator.createRandPillarRoom(biome);
  }

  // create floor
  float floorThickness = 4;
  createFloor(mapWidth, mapHeight, floorThickness);
  // create ceiling
  float ceilingThickness = 4;
  createCeiling(mapWidth, mapHeight, ceilingThickness);
}

void MapCreator::createFloorModel(vec2 origin, int width, int height, TextureType textureType) {
  Model* floorModel = getBoxModel(width, 4, height, 1);

  auto floor = gCoordinator.CreateEntity();
  gCoordinator.AddComponent(floor, Transform{.translation = T(origin.y, 0, origin.x),
                                             Ry(0)});  // we define the floor's origin at the bottom left corner
  gCoordinator.AddComponent(floor, Renderable{.model = floorModel, .shader = TERRAIN, .texture = textureType});
}
