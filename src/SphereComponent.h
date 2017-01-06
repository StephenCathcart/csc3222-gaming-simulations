#ifndef SPHERECOMPONENT
#define	SPHERECOMPONENT

#include "GameComponent.h"

/// <summary>
/// Sphere components hold mass information.
/// </summary>
class SphereComponent : public GameComponent {
public:
	SphereComponent(float mass);
	~SphereComponent(void);

	void  update ( float msec ) {};
	float getMass() const { return m_mass; }

private:
	float m_mass;
};

#endif