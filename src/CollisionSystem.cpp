#include "CollisionSystem.h"
#include <math.h>
#include "GameSystemManager.h"
#include "MovementComponent.h"
#include "RenderComponent.h"
#include "SphereComponent.h"
#include "PlaneComponent.h"
#include "PlaneCollisionMessage.h"
#include "SphereCollisionMessage.h"
#include "CollisionData.h"

/// <summary>
/// Initializes a new instance of the <see cref="CollisionSystem"/> class.
/// </summary>
CollisionSystem::CollisionSystem(void) {
}

/// <summary>
/// Finalizes an instance of the <see cref="CollisionSystem"/> class.
/// </summary>
CollisionSystem::~CollisionSystem(void) {
}

/// <summary>
/// Updates all entities that could collide.
/// </summary>
/// <param name="delta">The delta.</param>
/// <param name="resourceManager">The resource manager.</param>
/// <param name="entityManager">The entity manager.</param>
/// <param name="systemManager">The system manager.</param>
void CollisionSystem::update(float delta, GameResourceManager& resourceManager, GameEntityManager& entityManager, GameSystemManager& systemManager) {
	//Check collision with spheres
	vector<GameEntity*> sphereEntities = entityManager.getEntitiesWithComponentType<SphereComponent>();
	vector<GameEntity*> planeEntities = entityManager.getEntitiesWithComponentType<PlaneComponent>();

	// Detect collision functions
	checkPlaneCollision(systemManager, sphereEntities, planeEntities);
	checkSphereCollision(systemManager, sphereEntities);
}

/// <summary>
/// Detects sphere-plane collisions.
/// </summary>
/// <param name="mgr">Game system manager.</param>
/// <param name="sphereEntities">Sphere entities.</param>
/// <param name="planeEntities">The plane entities.</param>
void CollisionSystem::checkPlaneCollision(GameSystemManager& mgr, vector<GameEntity*> sphereEntities, vector<GameEntity*> planeEntities) {
	// For every sphere entity
	for(int i = 0; i < sphereEntities.size(); i++) {
		// Extract the spheres movement component
		MovementComponent*	spherePosition	= (MovementComponent*)sphereEntities[i]->getComponent<MovementComponent>();

		// For every plane entity
		for(int j = 0; j < planeEntities.size(); j++) { 
			// Extract the planes render and position components
			RenderComponent*	planeRender	= (RenderComponent*)planeEntities[j]->getComponent<RenderComponent>();
			MovementComponent*	planePos	= (MovementComponent*)planeEntities[j]->getComponent<MovementComponent>();

			float		r = spherePosition->getRadius();					// Get the spheres radius
			glm::vec3	N = planeRender->getMesh().getPlaneNormal();		// Get the planes normal
			glm::vec3	S = glm::vec3(spherePosition->getOrigin());			// Get the spheres centre point
			float		d = -glm::dot(planeRender->getMesh().getV0(), N);	// Calculate the distance
			
			// If the distance is less that the radius
			if(glm::dot(N, S) + d <= r) { 
				// There is a collision, send a plane-sphere collision message out to other systems which includes the
				// collision response data (the physics is handled in the physics system)
				float		pen = r - (glm::dot(N, S) + d); // The penetration amount
				glm::vec3	P	= S - N * (r - pen);		// The point of contact
				mgr.sendMessage(&PlaneCollisionMessage(CollisionData(pen, P, N),
													   sphereEntities[i], planeEntities[j]));
			}
		}
	}
}

/// <summary>
/// Detects sphere-sphere collisions. It first performs a quick broadphase sweep before computing
///	the narrowphase detection.
/// </summary>
/// <param name="mgr">The MGR.</param>
/// <param name="sphereEntities">The sphere entities.</param>
void CollisionSystem::checkSphereCollision(GameSystemManager& mgr, vector<GameEntity*> sphereEntities) {
	// For each sphere
	for(int i = 0; i < sphereEntities.size(); i++) {
		// Check against other spheres
		for(int j = 0; j < sphereEntities.size(); j++) {
			// Unless it is the same sphere
			if(*sphereEntities[i] != *sphereEntities[j]) {
				// Do a quick broadphase test to avoid unnessessary computation
				if(broadPhaseTest(sphereEntities[i], sphereEntities[j])) {
					// Extract both spheres movement component
					MovementComponent* iMovement = (MovementComponent*)sphereEntities[i]->getComponent<MovementComponent>();
					MovementComponent* jMovement = (MovementComponent*)sphereEntities[j]->getComponent<MovementComponent>();

					glm::vec3	relPos	= iMovement->getPosition() - jMovement->getPosition();				// Gets releative position
					float		dist	= relPos.x * relPos.x + relPos.y * relPos.y + relPos.z * relPos.z;	// the combined distance
					float		minDist = iMovement->getRadius() + jMovement->getRadius();					// The minimum distance for collision

					if(dist <= minDist * minDist) { // Check if distance is less than radii
						float		pen = iMovement->getRadius() + jMovement->getRadius() - sqrt(dist);		// The penetration amount
						glm::vec3	N   = glm::normalize(iMovement->getOrigin() - jMovement->getOrigin());	// The normal of collision
						glm::vec3	P	= iMovement->getOrigin() - N * (iMovement->getRadius() - pen);		// The point of contact

						// There is a collision, send a sphere-sphere collision message out to other systems which includes the
						// collision response data (the physics is handled in the physics system)
						mgr.sendMessage(&SphereCollisionMessage(CollisionData(pen, P, N),
																sphereEntities[i], sphereEntities[j]));
					}
				}
			}
		}
	}
}

/// <summary>
/// Broadphase test: quickly checks the extities y axis positions 
/// and decides if a collision would be possible.
/// </summary>
/// <param name="entity1">The entity1.</param>
/// <param name="entity2">The entity2.</param>
/// <returns></returns>
bool CollisionSystem::broadPhaseTest(GameEntity* entity1, GameEntity* entity2) {
	// Get the entities movement components
	MovementComponent* e1 = (MovementComponent*)entity1->getComponent<MovementComponent>();
	MovementComponent* e2 = (MovementComponent*)entity2->getComponent<MovementComponent>();

	float yDist	= e2->getPosition().y - e1->getPosition().y;
	int radii	= e1->getRadius() + e2->getRadius();

	// Is the y distance squared less than the combined radii squared
	return yDist * yDist < radii * radii;
}

/// <summary>
/// Receives Messages from other systems.
/// </summary>
/// <param name="msg">The MSG.</param>
void CollisionSystem::receiveMessage(BaseMessage* msg) {
}