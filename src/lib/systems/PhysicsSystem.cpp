#include "PhysicsSystem.hpp"

#include "components/Gravity.hpp"
#include "components/RigidBody.hpp"
#include "components/Transform.hpp"
#include "core/Coordinator.hpp"

extern Coordinator gCoordinator;

void PhysicsSystem::Init() { printf("PhysicsSystem Init\n"); };
void PhysicsSystem::Update() {
  for (auto const& entity : mEntities) {
    auto& transform = gCoordinator.GetComponent<Transform>(entity);
    auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
    auto& gravity = gCoordinator.GetComponent<Gravity>(entity);
    if (rigidBody.isStatic) {
      continue;
    }
    rigidBody.velocity += gravity.acceleration;
    transform.translation.m[3] += rigidBody.velocity.x;
    transform.translation.m[7] += rigidBody.velocity.y;
    transform.translation.m[11] += rigidBody.velocity.z;
  }
};