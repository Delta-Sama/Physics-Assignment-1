#pragma once
#ifndef __PROJECTILE_MANAGER_H__
#define __PROJECTILE_MANAGER_H__
#include <vector>
#include <GLM/detail/type_vec2.hpp>

#include "WayPoint.h"

class ProjectileManager
{
public:
	static float getSpeed() { return m_speed; }
	static float getAngle() { return m_angle; }
	static float getDistance() { return m_distance; }

	static void update();

	static glm::vec2 calculatePositionWithTime(float time);

	static void changeSpeed(float num);
	
	static void changeDistance(float num);
	
private:
	ProjectileManager();
	~ProjectileManager();

	static void changeAngle(float num);
	
	static float m_speed;
	static float m_angle;
	static float m_distance;

	static std::vector<WayPoint*> m_points;
};

typedef ProjectileManager PROMA;

#endif