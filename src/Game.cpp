#include "Game.h"
#include <cstdlib>
#include <ctime>

#include "Paths.h"
#include "GameEntity.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "RenderingSystem.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "SphereComponent.h"
#include "PlaneComponent.h"

// As game is capped to XY coordinates, set default Z value
const int Game::FACES = 6;

/// <summary>
/// Initializes a new instance of the <see cref="Game"/> class.
/// </summary>
Game::Game(void) {
}

/// <summary>
/// Memory cleaned up in shutdown function.
/// </summary>
Game::~Game(void) {
}

/// <summary>
/// Runs the game loop.
/// </summary>
void Game::run() {
	srand(time(0));

	initWindow();
	initResources();
	initSystems();
	initEntities();

	sf::Clock clock;
	while (m_systemManager->getIsActive()) {
		float delta = clock.restart().asMilliseconds();
		m_systemManager->update(delta, *m_resourceManager, *m_entityManager);
	}
	shutdown();
}

/// <summary>
/// Initializes the window.
/// </summary>
void Game::initWindow() {
	// Initialise window
	m_window = new sf::RenderWindow(sf::VideoMode(1080, 720), "CSC3222: Gaming Simulations", sf::Style::Default, sf::ContextSettings(32));

	// Enable VSync
	m_window->setVerticalSyncEnabled(true);
}

/// <summary>
/// Initializes the resources.
/// </summary>
void Game::initResources() { 
	// Initialise resource manager
	m_resourceManager = new GameResourceManager;

	// Load meshes
	m_resourceManager->addObjMesh(Paths::OBJ_BALL);
	m_resourceManager->addObjMesh(Paths::OBJ_PLANE_FRONT);
	m_resourceManager->addObjMesh(Paths::OBJ_PLANE_BACK);
	m_resourceManager->addObjMesh(Paths::OBJ_PLANE_LEFT);
	m_resourceManager->addObjMesh(Paths::OBJ_PLANE_RIGHT);
	m_resourceManager->addObjMesh(Paths::OBJ_PLANE_TOP);
	m_resourceManager->addObjMesh(Paths::OBJ_PLANE_BOTTOM);

	// Load shaders
	m_resourceManager->addShader(Paths::SHADER_BALL, Paths::SHADER_VERT_BALL, Paths::SHADER_FRAG_BALL);
	m_resourceManager->addShader(Paths::SHADER_PLANE, Paths::SHADER_VERT_PLANE, Paths::SHADER_FRAG_PLANE);
}

/// <summary>
/// Initializes the systems.
/// </summary>
void Game::initSystems() {
	// Initialise system manager responsible for input, logic, physics and render systems
	m_systemManager = new GameSystemManager(*m_window);

	// Load Systems
	m_systemManager->addSystem(new InputSystem(*m_window));
	m_systemManager->addSystem(new CollisionSystem);
	m_systemManager->addSystem(new PhysicsSystem);
	m_systemManager->addSystem(new RenderingSystem(*m_window));
}

/// <summary>
/// Initializes the entities.
/// </summary>
void Game::initEntities() {
	// Initialise entity manager
	m_entityManager = new GameEntityManager;

	// Initialise 15 random spheres
	for(int i = 0; i < 15; i++) {
		const float PADDING = 0.1f;
		float positionX  = randomFloat(-10.0f, 10.0f) + PADDING;
		float positionY  = randomFloat(8.0f, 17.0f) + PADDING;
		float positionZ  = randomFloat(-10.0f, 10.0f) + PADDING;
		float velocityX  = randomFloat(-50.0f, 50.0f) + PADDING;
		float velocityY  = randomFloat(-50.0f, 50.0f) + PADDING;
		float velocityZ  = randomFloat(-50.0f, 50.0f) + PADDING;
		float scale		 = randomFloat(1.0f, 2.0f);					// Scale for different sized spheres
		float mass		 = randomFloat(0.001f, 0.2f) * scale;		// Give bigger spheres more mass
		float elasticity = randomFloat(0.0f, 0.1f);					// Give the spheres some elasticity

		GameEntity* e = new GameEntity;
		e->addComponent(new RenderComponent(*m_resourceManager->getMesh(Paths::OBJ_BALL), *m_resourceManager->getShader(Paths::SHADER_BALL)));
		RenderComponent* render = (RenderComponent*)e->getComponent<RenderComponent>();
		e->addComponent(new MovementComponent(0.0f, glm::vec3(positionX, positionY, positionZ), glm::vec3(velocityX, velocityY, velocityZ), mass, render->getMesh().getRadius() * scale));
		e->addComponent(new SphereComponent(100.0f));

		m_entityManager->addEntity(e);
	}

	const std::string faces[FACES] = { Paths::OBJ_PLANE_FRONT , Paths::OBJ_PLANE_BACK, 
									   Paths::OBJ_PLANE_LEFT  , Paths::OBJ_PLANE_RIGHT, 
									   Paths::OBJ_PLANE_TOP	  , Paths::OBJ_PLANE_BOTTOM };
	// Initialise cube faces
	for(int i = 0; i < FACES; i++) {
		GameEntity* e = new GameEntity;
		e->addComponent(new RenderComponent(*m_resourceManager->getMesh(faces[i]), *m_resourceManager->getShader(Paths::SHADER_PLANE)));
		e->addComponent(new MovementComponent(0.0f, glm::vec3(0.0f)));
		e->addComponent(new PlaneComponent);
		m_entityManager->addEntity(e);
	}
}

/// <summary>
/// Clean up memory.
/// </summary>
void Game::shutdown() {
	delete m_window;
	delete m_systemManager;
	delete m_entityManager;
	delete m_resourceManager;
}

/// <summary>
/// Returns a random float between two floats.
/// </summary>
/// <param name="min">The minimum.</param>
/// <param name="max">The maximum.</param>
/// <returns></returns>
float Game::randomFloat(float min, float max) {
	float random = ((float)rand()) / (float) RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

/// <summary>
///Returns a random int between two ints.
/// </summary>
/// <param name="min">The minimum.</param>
/// <param name="max">The maximum.</param>
/// <returns></returns>
int Game::randomInt(int min, int max) {
	return (rand()%(max-min))+min;
}