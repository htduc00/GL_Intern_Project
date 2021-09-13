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
	if (m_level == 1) {
		bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture("MagicBullet1.tga"));
		bullet->SetSlow(0.3f);
	}
	if (m_level == 2) {
		bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture("MagicBullet2.tga"));
		bullet->SetSlow(0.5f);
	}
	bullet->SetDamage(m_damage);
	bullet->Set2DPosition(m_position.x, m_position.y - 40);
	bullet->SetTarget(target);
	bullet->SetSize(28, 28);
	bullet->setNumFrames(4);
	bullet->SetActive(true);
}

