#include "RenderingSystem.h"
#include "Paths.h"
#include "GameSystemManager.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "SphereComponent.h"
#include "KeyEventMessage.h"

#include <sstream>

/// <summary>
/// Initializes a new instance of the <see cref="RenderingSystem"/> class.
/// </summary>
/// <param name="window">The window.</param>
RenderingSystem::RenderingSystem(sf::RenderWindow &window) : m_window(window) {
	m_camera = new Camera(window);
	switchToPerspective(window);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Default view
	m_camera->setPosition(glm::vec3(0.0f, 10.0f, 40.0f));

	// FOR DEBUGGING ONLY
	m_isProfiling	= false;
	m_hasCollision	= false;
	if (!m_debugFont.loadFromFile(Paths::FONT_ARIAL)) {
		throw "Error loading font!"; 
	}
	m_debugText.setFont(m_debugFont);
	m_debugText.setScale(0.7f, 0.7f);
	m_debugText.setColor(sf::Color::Yellow);
	m_debugText.setString("FPS");
}

/// <summary>
/// Finalizes an instance of the <see cref="RenderingSystem"/> class.
/// </summary>
RenderingSystem::~RenderingSystem(void) {
	delete m_camera;
}

/// <summary>
/// Renders all Render Components to the window.
/// </summary>
/// <param name="delta">The delta.</param>
/// <param name="manager">The entity manager.</param>
/// <param name="systemManager">The system manager.</param>
void RenderingSystem::update(float delta, GameResourceManager& resourceManager, GameEntityManager& entityManager, GameSystemManager& systemManager) {
	glClearColor( 0.2f ,0.2f ,0.2f ,1.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_FPS.update();

	m_camera->updateCamera(delta);
	m_viewMatrix = m_camera->buildViewMatrix();

	// Get required Entities
	vector<GameEntity*> renderEntities = entityManager.getEntitiesWithComponentType<RenderComponent>();

	// Draw all renderable entities
	for (vector<GameEntity*>::iterator i = renderEntities.begin(); i != renderEntities.end(); ++i) {
		if((*i)->hasComponent<MovementComponent>()) {

			RenderComponent* rComp = (RenderComponent*)(*i)->getComponent<RenderComponent>();
			MovementComponent* mComp = (MovementComponent*)(*i)->getComponent<MovementComponent>();
			
			m_modelMatrix = glm::translate(glm::mat4(), 
				glm::vec3(mComp->getOrigin())) * 
				glm::rotate(glm::mat4(), mComp->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(glm::mat4(), mComp->getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(glm::mat4(), mComp->getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

			if((*i)->hasComponent<SphereComponent>()) {
				m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(mComp->getRadius()));
			}

			GLuint program = rComp->getShader().getShaderProgram();
			glUseProgram (program);
			
			updateShaderMatrices(program);
			glUniform1i(glGetUniformLocation(program, "colourTex"),	0);

			rComp->getMesh().draw();
			if(m_isProfiling) { // Show bounding boxes
				rComp->getMesh().drawBoundingBox(&rComp->getMesh(), m_modelMatrix);
			}

			glUseProgram(0);
		}
	}

	// Push/Pop states to avoid OpenGL and SFML clashing
	m_window.pushGLStates();
	if(m_isProfiling){
		displayDebug(delta, entityManager);
	}
	m_window.popGLStates();
	m_window.display();
}

void RenderingSystem::displayDebug(float delta, GameEntityManager& entityManager) {
	/******** DRAW DEBUG TEXT ********/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m_debugText.setPosition(10.0f, 10.0f);
	std::ostringstream buffer;
	buffer << m_FPS.getFPS();
	std::string str = "FPS: " + buffer.str();
	m_debugText.setString(str);
	m_window.draw(m_debugText);

	m_debugText.setPosition(10.0f, 40.0f);
	buffer.str( std::string() );
	buffer.clear();
	buffer << delta;
	str = "Delta: " + buffer.str();
	m_debugText.setString(str);
	m_window.draw(m_debugText);

	m_debugText.setPosition(10.0f, 70.0f);
	buffer.str( std::string() );
	buffer.clear();
	buffer << entityManager.getEnitiesAmount();
	str = "Entities: " + buffer.str();
	m_debugText.setString(str);
	m_window.draw(m_debugText);

	m_debugText.setPosition(10.0f, 100.0f);
	buffer.str( std::string() );
	buffer.clear();
	buffer << entityManager.getEntityComponentsAmount();
	str = "Components: " + buffer.str();
	m_debugText.setString(str);
	m_window.draw(m_debugText);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
}

/// <summary>
/// Receives System messages.
/// </summary>
/// <param name="msg">The MSG.</param>
void RenderingSystem::receiveMessage(BaseMessage* msg) {
	if(msg->getMessageType() == MessageType::KEYEVENT) {
		KeyEventMessage* e = dynamic_cast<KeyEventMessage*>(msg);
		if(e->getPayload().type == sf::Event::Resized) {
			// Adjust the viewport when the window is resized
			glViewport(0, 0, e->getPayload().size.width, e->getPayload().size.height);
			m_window.setView(sf::View(sf::FloatRect(0, 0, e->getPayload().size.width,  e->getPayload().size.height)));
		}

		// DEBUG MODE
		if(e->getPayload().key.code == sf::Keyboard::Num1) {
			m_isProfiling ? glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
			m_isProfiling = !m_isProfiling;
		}

		// CAMERA
		if(e->getPayload().key.code == sf::Keyboard::W) {
			m_camera->keyW();
		}
		if(e->getPayload().key.code == sf::Keyboard::A) {
			m_camera->keyA();
		}
		if(e->getPayload().key.code == sf::Keyboard::S) {
			m_camera->keyS();
		}
		if(e->getPayload().key.code == sf::Keyboard::D) {
			m_camera->keyD();
		}
		if(e->getPayload().key.code == sf::Keyboard::LShift) {
			m_camera->keyShift();
		}
		if(e->getPayload().key.code == sf::Keyboard::Space) {
			m_camera->keySpace();
		}
	}
}

/// <summary>
/// Updates the shader matrices.
/// </summary>
/// <param name="program">The program.</param>
void RenderingSystem::updateShaderMatrices(GLuint program)	{
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix")  , 1, false, (float*)&m_modelMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix")   , 1, false, (float*)&m_viewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix")   , 1, false, (float*)&m_projMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "textureMatrix"), 1, false, (float*)&m_textureMatrix);
}

/// <summary>
/// Switches to perspective mode.
/// </summary>
/// <param name="window">The window.</param>
void RenderingSystem::switchToPerspective(sf::RenderWindow &window) {
	setProjectionMatrix(glm::perspective(45.0f, (float)window.getSize().x / (float)window.getSize().y, 1.0f, 4500.0f));
}