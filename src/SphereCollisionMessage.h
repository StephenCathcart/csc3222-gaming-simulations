#ifndef SPHERECOLLISIONMESSAGE_H
#define SPHERECOLLISIONMESSAGE_H

#include "BaseMessage.h"
#include "GameEntity.h"
#include "CollisionData.h"

class SphereCollisionMessage : public BaseMessage {
public:
	SphereCollisionMessage(CollisionData& data, GameEntity* sphere1, GameEntity* sphere2);
	~SphereCollisionMessage(void);

	MessageType		getMessageType() const	{ return m_type; }
	CollisionData&	getData() const			{ return m_data; }
	GameEntity*		getSphereOne()			{ return m_sphere1; }
	GameEntity*		getSphereTwo()			{ return m_sphere2; }

private:
	MessageType		m_type;
	CollisionData&	m_data;
	GameEntity*		m_sphere1;
	GameEntity*		m_sphere2;
};

#endif
