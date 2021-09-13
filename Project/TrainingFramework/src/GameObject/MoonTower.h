#pragma once
#include "Tower.h"

class MoonTower : public Tower
{
public:
	MoonTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		int damage, int range, int gold);
	~MoonTower();

	void Upgrade();
	void Fire(std::shared_ptr<Enemy> target);
};