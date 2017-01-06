#include "SphereCollisionMessage.h"

/// <summary>
/// Initializes a new instance of the <see cref="SphereCollisionMessage"/> class.
/// </summary>
/// <param name="data">The data.</param>
/// <param name="sphere1">The sphere1.</param>
/// <param name="sphere2">The sphere2.</param>
SphereCollisionMessage::SphereCollisionMessage(CollisionData& data, GameEntity* sphere1, GameEntity* sphere2) 
	: m_data(data) {
	m_type		= MessageType::SPHERECOLLISION;
	m_sphere1	= sphere1;
	m_sphere2	= sphere2;
}

/// <summary>
/// Finalizes an instance of the <see cref="SphereCollisionMessage"/> class.
/// </summary>
SphereCollisionMessage::~SphereCollisionMessage(void) {
}
