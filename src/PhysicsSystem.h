#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "GameSystem.h"
#include "GameEntity.h"

/// <summary>
/// System responsible for updating the velocities and positions of
/// entities with Position & Velocity Components.
/// </summary>
class PhysicsSystem : public GameSystem {
public:
	PhysicsSystem(void);
	~PhysicsSystem(void);

	void update(float delta, GameResourceManager& resourceManager, GameEntityManager& entityManager, GameSystemManager& systemManager);
	void receiveMessage(BaseMessage* msg);

	void updateSpherePhysics(GameEntity* sphere, float dt);
	void penetrationResolution(GameEntity* sphere, float penetration, glm::vec3 normal);
	void applyImpulse(GameEntity* sphereOne, GameEntity* sphereTwo, glm::vec3 normal);

private:
	GameEntityManager*	m_entityManager;
	static const float	MSEC;
	static const float	PENETRATION_SLOP;
	static const float  GRAVITY;
	static const float  DAMPING;

	float				m_fps;
	float				m_dt;
	float				m_accumulator;
};

#endif
