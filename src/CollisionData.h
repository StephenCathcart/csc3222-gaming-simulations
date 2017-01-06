#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include "glm\glm.hpp"

/// <summary>
/// Contains information about a collision such as the point of contact, the normal and the
///	penetration amount.
/// </summary>
class CollisionData {
public:
	CollisionData(float penetration, glm::vec3 point, glm::vec3 normal = glm::vec3());
	~CollisionData(void);

	glm::vec3	getPoint() const		{ return m_point; }
	glm::vec3	getNormal() const		{ return m_normal; }
	float		getPenetration() const	{ return m_penetration; }

private:
	glm::vec3	m_point;
	glm::vec3	m_normal;
	float		m_penetration;
};

#endif