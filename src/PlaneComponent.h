#ifndef PLANECOMPONENT_H
#define PLANECOMPONENT_H

#include "GameComponent.h"

class PlaneComponent : public GameComponent {
public:
	PlaneComponent(void);
	~PlaneComponent(void);

	void update ( float msec )	{};
};

#endif