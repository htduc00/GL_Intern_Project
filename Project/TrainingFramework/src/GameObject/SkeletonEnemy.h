#pragma once
#include "Enemy.h"

class SkeletonEnemy : public Enemy
{
public:
	SkeletonEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		Direction dir, int HP, int Damage, float speed, int gold);
	~SkeletonEnemy();

	void		Move(GLfloat deltatime);
	void		MoveUp() override;
	void		MoveDown() override;
	void		MoveLeft() override;
	void		MoveRight() override;
	void		Stop() override;
};