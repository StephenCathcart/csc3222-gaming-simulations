#include "PlaneCollisionMessage.h"

/// <summary>
/// Initializes a new instance of the <see cref="PickUpCollisionEvent" /> class.
/// </summary>
/// <param name="entity">The entity.</param>
PlaneCollisionMessage::PlaneCollisionMessage(CollisionData& data, GameEntity* sphere, GameEntity* plane) 
	: m_data(data) {
	m_type		= MessageType::PLANECOLLISION;
	m_sphere	= sphere;
	m_plane		= plane;
}

/// <summary>
/// Finalizes an instance of the <see cref="PickUpCollisionEvent"/> class.
/// </summary>
PlaneCollisionMessage::~PlaneCollisionMessage(void) {
}
