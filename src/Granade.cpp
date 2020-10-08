#include "Granade.h"
#include "TextureManager.h"

Granade::Granade()
{
	TextureManager::Instance()->load("../Assets/textures/Granade.png", "granade");

	setWidth(15);
	setHeight(15);

	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);
}

Granade::~Granade()
= default;

void Granade::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const float ang = getTransform()->rotation.x;
	
	TextureManager::Instance()->draw("granade", x, y, ang, 255, true, SDL_FLIP_NONE, { getWidth(),getHeight() });
}

void Granade::update()
{

}

void Granade::clean()
{

}