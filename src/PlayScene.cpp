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

	m_pEnemies->getTransform()->position = glm::vec2(Config::START_POINT + PROMA::getDistance() * Config::MET_TO_PIX,
		Config::START_Y - m_pEnemies->getHeight() / 2);

	m_pDistanceLabel->setText("Distance = " + std::to_string(PROMA::getDistance()));
	m_pAngleToThrowLabel->setText("Angle = " + std::to_string(PROMA::getAngle()));
	m_pSpeedLabel->setText("Current speed = " + std::to_string(PROMA::getSpeed()));

	//m_pVelx->setText("vel x = " + std::to_string(m_pPlayer->getRigidBody()->velocity.x));
	//m_pVely->setText("vey x = " + std::to_string(m_pPlayer->getRigidBody()->velocity.y));
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

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
	
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pDistanceLabel = new Label("Distance", "Consolas", 40, blue, glm::vec2(500.0f, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);

	const SDL_Color white_green = { 0, 200, 0, 255 };
	m_pAngleToThrowLabel = new Label("Angle", "Consolas", 40, white_green, glm::vec2(500.0f, 85.0f));
	m_pAngleToThrowLabel->setParent(this);
	addChild(m_pAngleToThrowLabel);

	m_pSpeedLabel = new Label("Speed", "Consolas", 40, blue, glm::vec2(500.0f, 130.0f));
	m_pSpeedLabel->setParent(this);
	addChild(m_pSpeedLabel);
}
