#pragma once
#ifndef __GRANADE_H__
#define __GRANADE_H__

#include "Sprite.h"

class Granade final : public Sprite
{
public:
	Granade();
	~Granade();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

};

#endif /* defined (__PLANE__) */
