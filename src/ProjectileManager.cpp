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

	const float time = calculateTime();

	for (int i = 1; i <= Config::WAYPOINTS; i++)
	{
		glm::vec2 pos = calculatePositionWithTime((static_cast<float>(i) / Config::WAYPOINTS) * time);
		WayPoint pWaypoint;
		pWaypoint.getTransform()->position = { Config::START_X + pos.x * Config::MET_TO_PIX,
			Config::START_Y - pos.y * Config::MET_TO_PIX };
		pWaypoint.draw();
		
		//m_points.push_back(pWaypoint);
	}
	
}

glm::vec2 ProjectileManager::calculatePositionWithTime(float time)
{
	
	const float x = 0 + m_speed * cos(glm::radians(m_angle)) * time;
	const float y = 0 + m_speed * sin(glm::radians(m_angle)) * time + (Config::g * pow(time,2)) / 2;
	
	return { x, y };
}

float ProjectileManager::calculateTime()
{
	const float time = (2 * m_speed * sin(glm::radians(m_angle))) / abs(Config::g);
	
	return time;
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
