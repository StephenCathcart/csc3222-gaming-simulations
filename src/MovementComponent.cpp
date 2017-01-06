#include "MovementComponent.h"


/// <summary>
/// Initializes a new instance of the <see cref="MovementComponent"/> class.
/// </summary>
/// <param name="restitution">The restitution.</param>
/// <param name="position">The position.</param>
/// <param name="velocity">The velocity.</param>
/// <param name="mass">The mass.</param>
/// <param name="radius">The radius.</param>
/// <param name="rotation">The rotation.</param>
MovementComponent::MovementComponent(float restitution, glm::vec3 position, glm::vec3 velocity, float mass, float radius,  glm::vec3 rotation) {
	m_restitution		= restitution;
	m_previousVelocity	= glm::vec3(0.0f);
	m_previousPosition	= glm::vec3(0.0f);
	m_position			= position;
	m_velocity			= velocity;
	m_mass				= mass;
	m_radius			= radius;
	m_rotation			= rotation;
	m_IsResting			= false;
}

/// <summary>
/// Finalizes an instance of the <see cref="PositionComponent"/> class.
/// </summary>
MovementComponent::~MovementComponent(void) {
}
