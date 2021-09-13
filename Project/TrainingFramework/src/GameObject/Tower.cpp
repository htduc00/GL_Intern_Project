#include "Tower.h"
#include "Enemy.h"

Tower::Tower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int damage, int range,int gold)
	:AnimationSprite(model, shader, texture), m_level(1), m_damage(damage), m_range(range), m_isHolding(false), m_goldUpgrade(gold),m_pBtClick(nullptr)
{
}

Tower::~Tower()
{
}

int Tower::getDamage()
{
	return m_damage;
}

int Tower::getRange()
{
	return m_range;
}

int Tower::getLevel()
{
	return m_level;
}

int Tower::getGoldUpgrade()
{
	return m_goldUpgrade;
}

float Tower::getDelay()
{
	return m_delay;
}

void Tower::setDelay(float delay)
{
	m_delay = delay;
}

void Tower::SetTowerPos(int towerPos)
{
	m_towerPos = towerPos;
}

int Tower::GetTowerPos()
{
	return m_towerPos;
}

void Tower::SetOnClick(void(*pBtClick)(Tower*))
{
	m_pBtClick = pBtClick;
}

bool Tower::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	bool isHandled = false;
	if (bIsPressed)
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2))
		{
			// The button is being pressed down
			m_isHolding = true;
		}
	}
	else
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2)
			&& m_isHolding == true)
		{
			// Only perform click action when the same button was pressed down and released
			m_pBtClick(this);
			isHandled = true;
		}
		m_isHolding = false;
	}
	return isHandled;
}

bool Tower::IsHolding()
{
	return m_isHolding;
}
