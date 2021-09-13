#pragma once
#include "AnimationSprite.h"
#include <memory>
class Enemy;
class Tower : public AnimationSprite
{
protected:
	void	(*m_pBtClick)(Tower*);
	int m_level;
	int m_damage;
	int m_range;
	bool m_isHolding;
	float m_delay = 0.0f;
	int m_goldUpgrade;
	int m_towerPos = 0;
public:
	Tower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,int damage, int range,int gold);
	~Tower();

	int getDamage();
	int getRange();
	int getLevel();
	int getGoldUpgrade();
	float getDelay();
	void setDelay(float delay);
	void SetTowerPos(int towerPos);
	int GetTowerPos();

	void	SetOnClick(void	(*pBtClick)(Tower*));
	bool	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHolding();
	virtual void Upgrade() = 0;
	virtual void Fire(std::shared_ptr<Enemy> target) = 0;

};