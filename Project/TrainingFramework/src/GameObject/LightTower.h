#pragma once
#include "Tower.h"

class LightTower : public Tower
{
public:
	LightTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, 
		int damage, int range, int gold);
	~LightTower();

	void Upgrade();
	void Fire(std::shared_ptr<Enemy> enemy);
};