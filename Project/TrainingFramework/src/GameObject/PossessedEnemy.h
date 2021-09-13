#pragma once
#include "Enemy.h"

class PossessedEnemy : public Enemy
{
public:
	PossessedEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		Direction dir, int HP, int Damage, float speed, int gold);
	~PossessedEnemy();

	void		Move(GLfloat deltatime);
	void		MoveUp() override;
	void		MoveDown() override;
	void		MoveLeft() override;
	void		MoveRight() override;
	void		Stop() override;
};