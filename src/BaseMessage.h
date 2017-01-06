#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H

/// <summary>
/// The message types which will be sent between GameSystems
/// </summary>
enum MessageType {
	BASE, KEYEVENT, PLANECOLLISION, SPHERECOLLISION
};

/// <summary>
/// An abstract base message which other messages will derive from.
/// A message encapsulates data for GameSystems to use.
/// </summary>
class BaseMessage {
public:
	BaseMessage(void);
	~BaseMessage(void);

	virtual MessageType getMessageType() const = 0;
};

#endif
