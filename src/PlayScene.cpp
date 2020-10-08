#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "ProjectileManager.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	PROMA::update();
}

void PlayScene::update()
{
	updateDisplayList();

	m_pEnemies->getTransform()->position = glm::vec2(Config::START_POINT + PROMA::getDistance() * Config::MET_TO_PIX - m_pEnemies->getWidth(),
		Config::START_Y - m_pEnemies->getHeight() / 2);

	m_pDistanceLabel->setText("Distance = " + std::to_string(static_cast<int>(PROMA::getDistance())) + " m");
	m_pAngleToThrowLabel->setText("Angle = " + std::to_string(PROMA::getAngle()));
	m_pSpeedLabel->setText("Speed = " + std::to_string(static_cast<int>(PROMA::getSpeed())) + " m\s");

	m_pTimeRequiredLabel->setText("Time required: " + std::to_string(PROMA::getTime()));
	m_pCurrentLandPosLabel->setText("Land pos.x: " + std::to_string(static_cast<int>(PROMA::getLandPos())));
	
	if (PROMA::getProjectile())
	{
		std::string pos = std::to_string(static_cast<int>((PROMA::getProjectile()->getTransform()->position.x - Config::START_X) * Config::PIX_TO_MET)) + ";"
           + std::to_string(static_cast<int>((Config::START_Y - PROMA::getProjectile()->getTransform()->position.y) * Config::PIX_TO_MET));
		m_pProjPositionLabel->setText("Proj: (" + pos + ")");
	}
	else
		m_pProjPositionLabel->setText(" ");
	
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (!PROMA::getSimulation())
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_Q))
		{
			PROMA::changeDistance(-Config::CHANGE_DIST);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_E))
		{
			PROMA::changeDistance(Config::CHANGE_DIST);
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_F))
		{
			PROMA::changeSpeed(-Config::CHANGE_SPEED);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_G))
		{
			PROMA::changeSpeed(Config::CHANGE_SPEED);
		}
		
		if (EventManager::Instance().getMouseButton(0))
		{
			PROMA::launchSimulation();
		}
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_R))
	{
		PROMA::reset();
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	// Label
	m_pWookiee = new Player();
	m_pWookiee->getTransform()->position = glm::vec2(Config::START_X, Config::START_Y - m_pWookiee->getHeight()/2);
	addChild(m_pWookiee);

	m_pEnemies = new Enemy();
	m_pEnemies->getTransform()->position = glm::vec2(850.0f, Config::START_Y - m_pEnemies->getHeight() / 2);
	addChild(m_pEnemies);
	
	const SDL_Color blue = { 0, 0, 55, 255 };
	m_pDistanceLabel = new Label("Distance", "Tusj", 30, blue, glm::vec2(260.0f, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);

	m_pAngleToThrowLabel = new Label("Angle", "Tusj", 30, blue, glm::vec2(260.0f, 75.0f));
	m_pAngleToThrowLabel->setParent(this);
	addChild(m_pAngleToThrowLabel);

	m_pSpeedLabel = new Label("Speed", "Tusj", 30, blue, glm::vec2(260.0f, 110.0f));
	m_pSpeedLabel->setParent(this);
	addChild(m_pSpeedLabel);

	m_pProjPositionLabel = new Label("Proj:", "Tusj", 30, blue, glm::vec2(260.0f, 145.0f));
	m_pProjPositionLabel->setParent(this);
	addChild(m_pProjPositionLabel);

	m_pTimeRequiredLabel = new Label("Time:", "Tusj", 30, blue, glm::vec2(750.0f, 40.0f));
	m_pTimeRequiredLabel->setParent(this);
	addChild(m_pTimeRequiredLabel);

	m_pCurrentLandPosLabel = new Label("Land x pos:", "Tusj", 30, blue, glm::vec2(750.0f, 75.0f));
	m_pCurrentLandPosLabel->setParent(this);
	addChild(m_pCurrentLandPosLabel);

	const SDL_Color light_blue = { 60, 60, 255, 255 };
	m_pInstuctionsLabel0 = new Label("R - reset", "Tusj", 30, light_blue, glm::vec2(750.0f, 140.0f));
	m_pInstuctionsLabel0->setParent(this);
	addChild(m_pInstuctionsLabel0);

	m_pInstuctionsLabel1 = new Label("Q|E - change distance", "Tusj", 30, light_blue, glm::vec2(750.0f, 175.0f));
	m_pInstuctionsLabel1->setParent(this);
	addChild(m_pInstuctionsLabel1);

	m_pInstuctionsLabel2 = new Label("F|G - change speed", "Tusj", 30, light_blue, glm::vec2(750.0f, 210.0f));
	m_pInstuctionsLabel2->setParent(this);
	addChild(m_pInstuctionsLabel2);

	m_pInstuctionsLabel3 = new Label("Mouse Click - Launch Simulation", "Tusj", 30, light_blue, glm::vec2(750.0f, 245.0f));
	m_pInstuctionsLabel3->setParent(this);
	addChild(m_pInstuctionsLabel3);
}
