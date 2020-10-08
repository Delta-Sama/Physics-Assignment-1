#pragma once
#ifndef __PROJECTILE_MANAGER_H__
#define __PROJECTILE_MANAGER_H__

#include <algorithm>
#include <GLM/detail/type_vec2.hpp>

#include "Granade.h"

class ProjectileManager
{
public:
	static float getSpeed() { return m_speed; }
	static float getAngle() { return m_angle; }
	static float getDistance() { return m_distance; }

	static void launchSimulation();
	static float getTime();
	static float getLandPos();

	static bool getSimulation() { return m_simulation; }
	
	static void update();
	static void reset();

	static Granade* getProjectile() { return m_projectile; }

	static glm::vec2 calculatePositionWithTime(float time);
	static float calculateTime();

	static void changeSpeed(float num);
	static void changeDistance(float num);

	static void setSpeed(float num) { m_speed = std::clamp(num, 0.0f, 9999.0f); }
	static void setDistance(float num) { m_distance = std::clamp(num, 0.0f, 9999.0f); }

	static void setTargetLock(bool mode) { m_targetLock = mode; }
	static bool getTargetLock() { return m_targetLock; }
	
private:
	ProjectileManager();
	~ProjectileManager();

	static void changeAngle(float num);

	static float m_timeVar;
	
	static bool m_targetLock;
	static bool m_simulation;
	
	static float m_speed;
	static float m_angle;
	static float m_distance;

	static float m_time;
	static float m_curtime;

	static Granade* m_projectile;
};

typedef ProjectileManager PROMA;

#endif