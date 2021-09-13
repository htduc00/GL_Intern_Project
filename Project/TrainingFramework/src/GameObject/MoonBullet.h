#pragma once
#include "AnimationSprite.h"

class Enemy;
class MoonBullet : public AnimationSprite
{
protected:
	int m_damage;
	float m_speed;
	Vector2 m_velocity = { 0,0 };
	bool m_isActive;
	std::shared_ptr<Enemy> m_target = nullptr;
public:
	MoonBullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int damage, float speed);
	~MoonBullet();

	void OnCollision();
	void Draw() override;
	void SetActive(bool isActive);
	bool GetActive();
	void Move(GLfloat deltatime);
	void Reset();
	void SetDamage(int damage);

	void SetTarget(std::shared_ptr<Enemy> target);
};