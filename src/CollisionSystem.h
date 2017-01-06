#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "GameSystem.h"
/// <summary>
/// System responsible for all collisions between entities. Collision boundry data
/// is calculated in the mesh class on creation. 
///	Contains two main functions for sphere-plane and sphere-sphere collision detection.
///	After detection it sends a message out containing all response data which will be 
/// picked up by physics system.
/// </summary>
class CollisionSystem : public GameSystem {
public:
	CollisionSystem(void);
	~CollisionSystem(void);

	void update(float delta, GameResourceManager& resourceManager, GameEntityManager& entityManager, GameSystemManager& systemManager);
	void receiveMessage(BaseMessage* msg);

	void checkPlaneCollision(GameSystemManager& mgr, vector<GameEntity*> sphereEntities, vector<GameEntity*> planeEntities);
	void checkSphereCollision(GameSystemManager& mgr, vector<GameEntity*> sphereEntities);

	bool broadPhaseTest(GameEntity* entity1, GameEntity* entity2);

};

#endif
