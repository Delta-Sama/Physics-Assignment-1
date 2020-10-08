#include "ProjectileManager.h"

#include <iostream>
#include <glm/detail/func_trigonometric.inl>

#include "Config.h"
#include "EventManager.h"

float PROMA::m_speed = 95.0f;
float PROMA::m_angle = 15.0f;
float PROMA::m_distance = 485.0f;

std::vector<WayPoint*> PROMA::m_points;


ProjectileManager::ProjectileManager() {}

ProjectileManager::~ProjectileManager() = default;

void ProjectileManager::update()
{
	const float y = 550.0f - EventManager::Instance().getMousePosition().y;
	const float x = EventManager::Instance().getMousePosition().x - 40.0f;

	const float ang = glm::degrees(atan2(y, x));

	changeAngle(ang);

	for (WayPoint* pWaypoint : m_points)
	{
		delete pWaypoint;
	}
	m_points.clear();

	
	
}

glm::vec2 ProjectileManager::calculatePositionWithTime(float time)
{
	float x = 0 + m_speed * cos(m_angle);
	float y = 0 + m_speed * sin(m_angle) + (Config::g * pow(time,2)) / 2;
	
	return { x, y };
}

void ProjectileManager::changeSpeed(float num)
{
	m_speed += num;
	if (m_speed < 0)
	{
		m_speed = 0;
	}
	else if (m_speed > Config::MAX_SPEED)
	{
		m_speed = Config::MAX_SPEED;
	}
}

void ProjectileManager::changeAngle(float num)
{
	m_angle = num;
	if (m_angle < Config::MIN_ANGLE)
	{
		m_angle = Config::MIN_ANGLE;
	}
	else if (m_angle > Config::MAX_ANGLE)
	{
		m_angle = Config::MAX_ANGLE;
	}
}

void ProjectileManager::changeDistance(float num)
{
	m_distance += num;
	if (m_distance < 0)
	{
		m_distance = 0;
	}
	else if (m_distance > Config::MAX_DIST)
	{
		m_distance = Config::MAX_DIST;
	}
}
