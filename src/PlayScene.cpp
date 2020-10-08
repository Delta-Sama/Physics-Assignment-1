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

	if (m_instructionsEnabled)
	{
		for (Label* label : m_instructions)
		{
			label->draw();
		}
	}
	else
		m_pShowInstuctionsLabel->draw();
}

void PlayScene::update()
{
	updateDisplayList();

	m_pEnemies->getTransform()->position = glm::vec2(Config::START_POINT + PROMA::getDistance() * Config::MET_TO_PIX - m_pEnemies->getWidth(),
		Config::START_Y - m_pEnemies->getHeight() / 2);

	m_pDistanceLabel->setText("Distance = " + std::to_string(static_cast<int>(PROMA::getDistance())) + " m");
	m_pAngleToThrowLabel->setText("Angle = " + std::to_string(PROMA::getAngle()));
	if (PROMA::getAngle() == 0.0f && PROMA::getDistance() != 0)
	{
		m_pAngleToThrowLabel->setText("impossible to reach");
	}
	m_pSpeedLabel->setText("Speed = " + std::to_string(static_cast<int>(PROMA::getSpeed())) + " m\s");

	m_pTimeRequiredLabel->setText("Time required: " + std::to_string(PROMA::getTime()) + " s");
	m_pCurrentLandPosLabel->setText("Land pos.x: " + std::to_string(static_cast<int>(PROMA::getLandPos())) + " m");
	
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

	for (Label* label : m_instructions)
	{
		delete label;
	}
	delete m_pShowInstuctionsLabel;
	m_instructions.clear();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (!PROMA::getSimulation())
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			PROMA::changeDistance(-Config::CHANGE_DIST);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			PROMA::changeDistance(Config::CHANGE_DIST);
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			PROMA::changeSpeed(-Config::CHANGE_SPEED);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			PROMA::changeSpeed(Config::CHANGE_SPEED);
		}
		
		if (EventManager::Instance().getMouseButton(0))
		{
			PROMA::launchSimulation();
		}

		if (EventManager::Instance().KeyPressed(SDL_SCANCODE_H))
		{
			m_instructionsEnabled = !m_instructionsEnabled;
		}

		if (EventManager::Instance().KeyPressed(SDL_SCANCODE_SPACE))
		{
			PROMA::setTargetLock(!PROMA::getTargetLock());
		}

		if (EventManager::Instance().KeyPressed(SDL_SCANCODE_T))
		{
			/*PROMA::setTargetLock(true);

			std::cout << "Enter desired speed: ";
			float temp_speed;
			std::cin >> temp_speed;
			PROMA::setSpeed(temp_speed);

			std::cout << "Enter desired distance: ";
			float temp_dist;
			std::cin >> temp_dist;
			PROMA::setDistance(temp_dist);*/
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
	m_instructionsEnabled = true;
	
	// Label
	m_pBackground = new Background();
	m_pBackground->getTransform()->position = glm::vec2(0.0f, 0.0f);
	addChild(m_pBackground);
	
	m_pWookiee = new Player();
	m_pWookiee->getTransform()->position = glm::vec2(Config::START_X, Config::START_Y - m_pWookiee->getHeight()/2);
	addChild(m_pWookiee);

	m_pEnemies = new Enemy();
	m_pEnemies->getTransform()->position = glm::vec2(850.0f, Config::START_Y - m_pEnemies->getHeight() / 2);
	addChild(m_pEnemies);

	const SDL_Color white = { 255, 255, 255, 255 };
	m_pDistanceLabel = new Label("Distance", "Tusj", 30, white, glm::vec2(160.0f, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);

	m_pAngleToThrowLabel = new Label("Angle", "Tusj", 30, white, glm::vec2(160.0f, 75.0f));
	m_pAngleToThrowLabel->setParent(this);
	addChild(m_pAngleToThrowLabel);

	m_pSpeedLabel = new Label("Speed", "Tusj", 30, white, glm::vec2(160.0f, 110.0f));
	m_pSpeedLabel->setParent(this);
	addChild(m_pSpeedLabel);

	m_pProjPositionLabel = new Label("Proj:", "Tusj", 30, white, glm::vec2(160.0f, 285.0f));
	m_pProjPositionLabel->setParent(this);
	addChild(m_pProjPositionLabel);

	m_pTimeRequiredLabel = new Label("Time:", "Tusj", 30, white, glm::vec2(750.0f, 20.0f));
	m_pTimeRequiredLabel->setParent(this);
	addChild(m_pTimeRequiredLabel);

	m_pCurrentLandPosLabel = new Label("Land x pos:", "Tusj", 30, white, glm::vec2(750.0f, 55.0f));
	m_pCurrentLandPosLabel->setParent(this);
	addChild(m_pCurrentLandPosLabel);

	const SDL_Color light_green = { 220, 255, 220, 255 };
	std::string instructions[] = { "H - close instructions", "R - reset" ,"A|D - change distance","W|S - change speed",
		"Mouse Click - Launch Simulation", "SPACE - target lock" };
	for (int i = 0; i < 6; i++)
	{
		Label* m_pInstuctionsLabel = new Label(instructions[i], "Tusj", 30, light_green, glm::vec2(750.0f, 140.0f + 35.0f * i));
		m_pInstuctionsLabel->setParent(this);
		m_instructions.push_back(m_pInstuctionsLabel);
	}

	m_pShowInstuctionsLabel = new Label("H - open instructions", "Tusj", 30, light_green, glm::vec2(750.0f, 140.0f));
	m_pCurrentLandPosLabel->setParent(this);
}
