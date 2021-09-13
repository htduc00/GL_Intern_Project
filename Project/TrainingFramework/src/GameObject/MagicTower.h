#pragma once
#include "Tower.h"

class MagicTower : public Tower
{
public:
	MagicTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		int damage, int range,int gold);
	~MagicTower();

	void Upgrade();
	void Fire(std::shared_ptr<Enemy> target);
};