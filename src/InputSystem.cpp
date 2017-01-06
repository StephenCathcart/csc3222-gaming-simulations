#include "InputSystem.h"
#include "GameSystemManager.h"
#include "KeyEventMessage.h"

const float InputSystem::JOY_THRESHOLD = 50.0f;

/// <summary>
/// Initializes a new instance of the <see cref="InputSystem"/> class.
/// </summary>
/// <param name="window">The window.</param>
InputSystem::InputSystem(sf::RenderWindow &window) : m_window(window) {
}

/// <summary>
/// Finalizes an instance of the <see cref="InputSystem"/> class.
/// </summary>
InputSystem::~InputSystem(void) {
}

/// <summary>
/// Polls for events.
/// </summary>
/// <param name="delta">The delta.</param>
/// <param name="manager">The manager.</param>
/// <param name="systemManager">The system manager.</param>
void InputSystem::update(float delta, GameResourceManager& resourceManager, GameEntityManager& entityManager, GameSystemManager& systemManager) {
	sf::Event e;
	while (m_window.pollEvent(e)) {
		handleKeyboard(systemManager, e);
	}
}

/// <summary>
/// Handles keyboard events.
/// </summary>
/// <param name="mgr">The MGR.</param>
/// <param name="e">The e.</param>
void InputSystem::handleKeyboard(GameSystemManager& mgr, sf::Event& e) {
	bool fireMsg = false;

	if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)) {
		mgr.setIsActive(false);
	}
	if (e.type == sf::Event::Resized) {
		fireMsg = true;
	}
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Num1 || e.key.code == sf::Keyboard::W ||
			e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::S ||
			e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Space ||
			e.key.code == sf::Keyboard::LShift) {
			fireMsg = true;
		}
	}
	if(e.type == sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::A ||
			e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::D ||
			e.key.code == sf::Keyboard::Space || e.key.code == sf::Keyboard::LShift) {
			fireMsg = true;
		}
	}
	if(fireMsg) {
		mgr.sendMessage(&KeyEventMessage(e));
	}
}

/// <summary>
/// Receives Messages from other Systems.
/// </summary>
/// <param name="msg">The MSG.</param>
void InputSystem::receiveMessage(BaseMessage* msg) {
}