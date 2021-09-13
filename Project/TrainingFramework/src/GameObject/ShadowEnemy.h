#pragma once
#include "Enemy.h"

class ShadowEnemy : public Enemy
{
public:
	ShadowEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		Direction dir, int HP, int Damage, float speed, int gold);
	~ShadowEnemy();

	void		Move(GLfloat deltatime);
	void		MoveUp() override;
	void		MoveDown() override;
	void		MoveLeft() override;
	void		MoveRight() override;
	void		Stop() override;
};