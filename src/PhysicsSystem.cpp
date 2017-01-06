#include "PhysicsSystem.h"
#include "GameSystemManager.h"
#include "SphereComponent.h"
#include "MovementComponent.h"
#include "PlaneCollisionMessage.h"
#include "SphereCollisionMessage.h"
#include <algorithm> 

const float PhysicsSystem::MSEC				= 0.0001f;
const float PhysicsSystem::PENETRATION_SLOP	= 0.02f;
const float PhysicsSystem::GRAVITY			= 100.0f;
const float PhysicsSystem::DAMPING			= 1.5f;

/// <summary>
/// Initializes a new instance of the <see cref="PhysicsSystem" /> class.
/// </summary>
PhysicsSystem::PhysicsSystem(void) {
	m_fps			= 100.0f;
	m_dt			= 1 / m_fps;
	m_accumulator	= 0.0f;
}


/// <summary>
/// Finalizes an instance of the <see cref="PhysicsSystem"/> class.
/// </summary>
PhysicsSystem::~PhysicsSystem(void) {
}

/// <summary>
/// Updates Entity Position and Velocity Components.
/// </summary>
/// <param name="delta">The delta.</param>
/// <param name="manager">The entity manager.</param>
/// <param name="systemManager">The system manager.</param>
void PhysicsSystem::update(float dt, GameResourceManager& resourceManager, GameEntityManager& entityManager, GameSystemManager& systemManager) {
	m_entityManager = &entityManager;
	dt *= MSEC;
	
	m_accumulator += dt;
	while(m_accumulator > m_dt) {
		// Update sphere physics
		vector<GameEntity*> sphereEntities = entityManager.getEntitiesWithComponentType<SphereComponent>();
		for(int i = 0; i < sphereEntities.size(); i++) {
			updateSpherePhysics(sphereEntities[i], dt);
		}
		m_accumulator -= dt;
	}
}

void PhysicsSystem::updateSpherePhysics(GameEntity* sphere, float dt) {
	if(sphere->hasComponent<MovementComponent>()) {
		/** Euler integration **/
		MovementComponent* mComp = (MovementComponent*)sphere->getComponent<MovementComponent>();
		/*if(glm::length(mComp->getVelocity()) < 0.01f) {
			mComp->setVelocity(glm::vec3(0.0f));
			mComp->setIsResting(true);
		}*/
		if(!mComp->getIsResting()) {
			glm::vec3 forces(0.0f);
			forces += glm::vec3(0.0f, -1.0f, 0.0f) * GRAVITY; 
			glm::vec3 acceleration = forces / ( mComp->getMass()); 

			mComp->setVelocity(mComp->getVelocity() + acceleration * dt);
			mComp->setPosition((mComp->getPosition() + (mComp->getVelocity()) * dt));
		}
	}
}

/// <summary>
/// Resolves the issue of a sphere penetrating another entiity.
/// </summary>
/// <param name="sphere">The sphere.</param>
/// <param name="penetration">The penetration amount.</param>
/// <param name="normal">The normal of collision.</param>
void PhysicsSystem::penetrationResolution(GameEntity* sphere, float penetration, glm::vec3 normal) {
	// Retrives the entities movement component.
	MovementComponent* mComp = (MovementComponent*)sphere->getComponent<MovementComponent>();

	// Calculate new position XYZ for the entity by pushing it along the normal by an amount relevant to the penetration
	// We also add a little bit of slop just to make sure the entity will no longer be inside another object.
	float x = (normal.x == 0.0f) ? mComp->getPosition().x : mComp->getPosition().x + (normal.x * penetration) + PENETRATION_SLOP;
	float y = (normal.y == 0.0f) ? mComp->getPosition().y : mComp->getPosition().y + (normal.y * penetration) + PENETRATION_SLOP;
	float z = (normal.z == 0.0f) ? mComp->getPosition().z : mComp->getPosition().z + (normal.z * penetration) + PENETRATION_SLOP;

	// Set new position.
	mComp->setPosition(glm::vec3(x, y, z));
}

/// <summary>
/// Applies an impulse to the involved entities.
/// </summary>
/// <param name="entityOne">Entity one.</param>
/// <param name="entityTwo">Entity two.</param>
/// <param name="normal">The normal taken from the collision detection algorithm.</param>
void PhysicsSystem::applyImpulse(GameEntity* entityOne, GameEntity* entityTwo, glm::vec3 normal) {
	// Retrive both entities movement component.
	MovementComponent* mComp1 = (MovementComponent*)entityOne->getComponent<MovementComponent>();
	MovementComponent* mComp2 = (MovementComponent*)entityTwo->getComponent<MovementComponent>();

	mComp1->setIsResting(false);
	mComp2->setIsResting(false);

	// Calculate inverse mass
	float invMass1 = (mComp1->getMass() == 0.0f) ? 1.0f : 1 / mComp1->getMass();
	float invMass2 = (mComp2->getMass() == 0.0f) ? 1.0f : 1 / mComp2->getMass();

	// If both entities are non movable (no mass between them) then return
	if ((invMass1 + invMass2) == 0.0 ) return;

	// Calculate the relative velocity
	glm::vec3 rv = mComp1->getVelocity() - mComp2->getVelocity();

	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = -glm::dot(rv, normal);

	// Return if the velocities are separating
	if(velAlongNormal < -0.01f ) { 
		return; 
	}

	// Coefficient of Restitution (elastically of object)
	// Always take the minimum elastically.
	float e = min(mComp1->getRestitution(), mComp2->getRestitution());

	// Calculate tangent vector
	glm::vec3 tangent = glm::vec3(0.0f);
	tangent = rv - (glm::dot(rv, normal) * normal);
	tangent = glm::normalize(tangent);

	// Calculate tangent impulse scalar
	float jt = -1.0f * glm::dot(rv, tangent);
	jt /= invMass1 + invMass2;

	// Calculate normal impulse scalar
	float jn = -(1.0f + e) * velAlongNormal;
	jn /= invMass1 + invMass2;

	// Apply both normal and tangent impulses to entities
	glm::vec3 normalImpulse = jn * normal;
	glm::vec3 tangentImpulse = jt * normal;
	mComp1->setVelocity(mComp1->getVelocity() - (invMass1 * normalImpulse));
	mComp1->setVelocity(mComp1->getVelocity() - (invMass1  * tangentImpulse));
	mComp2->setVelocity(mComp2->getVelocity() + (invMass2  * normalImpulse));
	mComp2->setVelocity(mComp2->getVelocity() + (invMass2  * tangentImpulse));
}

/// <summary>
/// Receives messages from other Systems (In the case of this coursework it recieves
///	collision messages from collision system).
/// </summary>
/// <param name="msg">The message from another system.</param>
void PhysicsSystem::receiveMessage(BaseMessage* msg) {
	// Listen for sphere to plane collision detection
	if(msg->getMessageType() == MessageType::PLANECOLLISION) {
		// Get message payload
		PlaneCollisionMessage* e	= dynamic_cast<PlaneCollisionMessage*>(msg);
		GameEntity* sphere			= e->getSphere();
		GameEntity* plane			= e->getPlane();
		float penetration			= e->getData().getPenetration();
		glm::vec3 normal			= e->getData().getNormal();

		// Now apply an impulse to entities and resolve penetration issues.
		applyImpulse(sphere, plane, normal);
		penetrationResolution(sphere, penetration, normal);
	}

	// Listen for sphere to sphere collision detection
	if(msg->getMessageType() == MessageType::SPHERECOLLISION) {
		// Get message payload
		SphereCollisionMessage* e	= dynamic_cast<SphereCollisionMessage*>(msg);
		GameEntity* sphereOne		= e->getSphereOne();
		GameEntity* sphereTwo		= e->getSphereTwo();
		float penetration			= e->getData().getPenetration();
		glm::vec3 normal			= e->getData().getNormal();

		// Now apply an impulse to entities and resolve penetration issues.
		applyImpulse(sphereOne, sphereTwo, normal);
		penetrationResolution(sphereOne, penetration, normal);
	}
}
