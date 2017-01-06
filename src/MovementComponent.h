#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "GameComponent.h"
#include "glm\glm.hpp"

/// <summary>
///	IMPORTANT: For simplicity I have grouped all information needed for this coursework into this
///	one component. Normally I would have seporate components for position, velocity etc.
/// Movement components holds all information needed for sphere collision detection and movement.
/// </summary>
class MovementComponent : public GameComponent {
public:
	MovementComponent(float restitution, glm::vec3 position, glm::vec3 velocity = glm::vec3(0.0f), 
				float mass = 0.0f, float radius = 0.0f,  glm::vec3 rotation = glm::vec3(0.0f));
	~MovementComponent(void);

	void		update ( float msec )	{};

	void		setIsResting(bool isResting)		{ m_IsResting = isResting; }
	bool		getIsResting() const				{ return m_IsResting; }
	bool		getRestitution() const				{ return m_restitution; }
	glm::vec3	getPrevVelocity() const				{ return m_previousVelocity; }
	void		setPrevVelocity(glm::vec3 velocity) { m_previousVelocity = velocity; }
	glm::vec3	getPosition() const					{ return m_position; }
	void		setPosition(glm::vec3 position)		{ m_position = position; }
	glm::vec3	getPrevPosition() const				{ return m_previousPosition; }
	void		setPrevPosition(glm::vec3 position) { m_previousPosition = position; }
	glm::vec3	getVelocity() const					{ return m_velocity; }
	void		setVelocity(glm::vec3 velocity)		{ m_velocity = velocity; }
	float		getMass() const						{ return m_mass; }
	float		getRadius() const					{ return m_radius; }
	glm::vec3	getRotation() const					{ return m_rotation; }
	void		setRotation(glm::vec3 rotation)		{ m_rotation = rotation; }
	glm::vec3	getOrigin() const					{ return glm::vec3(m_position.x + m_radius, m_position.y + m_radius, m_position.z + m_radius); }

private:
	float		m_restitution;
	glm::vec3	m_previousPosition;
	glm::vec3	m_position;
	glm::vec3	m_previousVelocity;
	glm::vec3	m_velocity;
	float		m_mass;
	float		m_radius;
	glm::vec3	m_rotation;
	bool		m_IsResting;
};

#endif