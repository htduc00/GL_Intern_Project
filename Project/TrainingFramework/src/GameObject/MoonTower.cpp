#include "MoonTower.h"
#include "ObjectPool.h"
#include "ResourceManagers.h"

MoonTower::MoonTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
	int damage, int range, int gold) : Tower(model, shader, texture,damage,range,gold)
{
}

MoonTower::~MoonTower()
{
}

void MoonTower::Upgrade()
{
	if (m_level == 2) return;
	else if (m_level == 1)
		SetTexture(ResourceManagers::GetInstance()->GetTexture("BloodMoonTower2.tga"));
	m_damage *= 1.5;
	m_range += 50;
	m_level += 1;
}

void MoonTower::Fire(std::shared_ptr<Enemy> target)
{
	MoonBullet* bullet = ObjectPool::GetInstance()->getMoonBullet();
	if (m_level == 1) {
		bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture("MoonBullet1.tga"));
		bullet->SetCrit(20);
	}
	if (m_level == 2) {
		bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture("MoonBullet2.tga"));
		bullet->SetCrit(40);
	}
	bullet->SetDamage(m_damage);
	bullet->Set2DPosition(m_position.x, m_position.y - 40);
	bullet->SetTarget(target);
	bullet->SetSize(24, 24);
	bullet->setNumFrames(4);
	bullet->SetActive(true);
}

