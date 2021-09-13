#include "MagicTower.h"
#include "ObjectPool.h"
#include "ResourceManagers.h"

MagicTower::MagicTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
	int damage, int range, int gold) : Tower(model, shader, texture,damage,range,gold)
{
}

MagicTower::~MagicTower()
{
}

void MagicTower::Upgrade()
{
	if (m_level == 2) return;
	else if (m_level == 1)
		SetTexture(ResourceManagers::GetInstance()->GetTexture("MagicTower2.tga"));
	m_damage *= 1.5;
	m_range += 50;
	m_level += 1;
}

void MagicTower::Fire(std::shared_ptr<Enemy> target)
{
	MagicBullet* bullet = ObjectPool::GetInstance()->getMagicBullet();
	if (m_level == 2)
		bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture("MagicBullet2.tga"));
	else if(m_level == 3)
		bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture("MagicBullet3.tga"));
	bullet->Set2DPosition(m_position.x, m_position.y - 40);
	bullet->SetTarget(target);
	bullet->SetSize(28, 28);
	bullet->setNumFrames(4);
	bullet->SetActive(true);
}

