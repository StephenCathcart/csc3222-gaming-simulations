#include "CollisionData.h"

/// <summary>
/// Initializes a new instance of the <see cref="CollisionData"/> class.
/// </summary>
/// <param name="penetration">The penetration amount.</param>
/// <param name="point">The point of contact.</param>
/// <param name="normal">The normal of the collision.</param>
CollisionData::CollisionData(float penetration, glm::vec3 point, glm::vec3 normal) {
	m_penetration = penetration;
	m_point = point;
	m_normal = normal;
}

/// <summary>
/// Finalizes an instance of the <see cref="CollisionData"/> class.
/// </summary>
CollisionData::~CollisionData(void) {
}