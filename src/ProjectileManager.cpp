#include "ProjectileManager.h"

#include <iostream>
#include <glm/detail/func_trigonometric.inl>

#include "Config.h"
#include "EventManager.h"
#include "WayPoint.h"

float PROMA::m_time = 0.0f;
float PROMA::m_curtime = 0.0f;

float PROMA::m_speed = Config::START_SPEED;
float PROMA::m_angle = Config::START_ANGLE;
float PROMA::m_distance = Config::START_DISTANCE;
float PROMA::m_timeVar = 0.0f;
bool PROMA::m_simulation = false;
bool PROMA::m_targetLock = false;

Granade* PROMA::m_projectile = nullptr;

ProjectileManager::ProjectileManager() {}

ProjectileManager::~ProjectileManager() = default;

void ProjectileManager::launchSimulation()
{
	if (!m_simulation)
	{
		m_simulation = true;

		m_time = calculateTime();
		m_curtime = 0.0f;

		m_projectile = new Granade();
	}
}

float ProjectileManager::getTime()
{
	return m_timeVar;
}

float ProjectileManager::getLandPos()
{
	return calculatePositionWithTime(m_timeVar).x;
}

void ProjectileManager::update()
{
	m_timeVar = calculateTime();
	
	if (!m_simulation)
	{
		if (!m_targetLock)
		{
			const float y = 550.0f - EventManager::Instance().getMousePosition().y;
			const float x = EventManager::Instance().getMousePosition().x - 40.0f;

			const float ang = glm::degrees(atan2(y, x));

			changeAngle(ang);
		}
		else
		{
			float sin2ang = (m_distance * -Config::g) / pow(m_speed, 2);
			const float ang = (abs(sin2ang) > 1 ? -1.0f : glm::degrees(asin(sin2ang)) / 2);
			
			changeAngle(ang);
		}

		const float time = calculateTime();

		for (int i = 1; i <= Config::WAYPOINTS; i++)
		{
			glm::vec2 pos = calculatePositionWithTime((static_cast<float>(i) / Config::WAYPOINTS) * time);
			WayPoint pWaypoint;
			pWaypoint.getTransform()->position = { Config::START_X + pos.x * Config::MET_TO_PIX,
                Config::START_Y - pos.y * Config::MET_TO_PIX };
			pWaypoint.draw();
		}
	}
	else
	{
		if (m_curtime < m_time)
		{
			m_curtime += 1.0f / Config::FPS;
			glm::vec2 pos = calculatePositionWithTime(m_curtime);

			m_projectile->getTransform()->position = { Config::START_X + pos.x * Config::MET_TO_PIX,
				Config::START_Y - pos.y * Config::MET_TO_PIX };
			m_projectile->getTransform()->rotation.x += 0.1;
			m_projectile->draw();
		}
		else
		{
			delete m_projectile;
			m_projectile = nullptr;
			
			m_simulation = false;
		}
	}
}

void ProjectileManager::reset()
{
	m_speed = Config::START_SPEED;
	m_distance = Config::START_DISTANCE;

	delete m_projectile;
	m_projectile = nullptr;
	
	m_simulation = false;
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
