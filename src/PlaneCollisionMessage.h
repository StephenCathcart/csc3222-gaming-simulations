#ifndef PLANECOLLISIONMESSAGE_H
#define PLANECOLLISIONMESSAGE_H

#include "BaseMessage.h"
#include "GameEntity.h"
#include "CollisionData.h"

/// <summary>
/// A PickUp Message holds a pointer to the pick up entity that
/// has been collected;
/// </summary>
class PlaneCollisionMessage : public BaseMessage {
public:
	PlaneCollisionMessage(CollisionData& data, GameEntity* sphere, GameEntity* plane);
	~PlaneCollisionMessage(void);

	MessageType		getMessageType() const	{ return m_type; }
	CollisionData&	getData() const			{ return m_data; }
	GameEntity*		getSphere()				{ return m_sphere; }
	GameEntity*		getPlane()				{ return m_plane; }

private:
	MessageType		m_type;
	CollisionData&	m_data;
	GameEntity*		m_sphere;
	GameEntity*		m_plane;
};

#endif