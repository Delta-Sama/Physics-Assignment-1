#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "WayPoint.h"
#include "Player.h"
#include "Button.h"
#include "Enemy.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	glm::vec2 m_mousePosition;

	Player* m_pWookiee;
	Enemy* m_pEnemies;
	
	Label* m_pDistanceLabel;
	Label* m_pAngleToThrowLabel;
	Label*  m_pSpeedLabel;
	Label* m_pProjPositionLabel;

	Label* m_pInstuctionsLabel0;
	Label* m_pInstuctionsLabel1;
	Label* m_pInstuctionsLabel2;
	Label* m_pInstuctionsLabel3;
	
	Label* m_pTimeRequiredLabel;
	Label* m_pCurrentLandPosLabel;
	
};

#endif /* defined (__PLAY_SCENE__) */