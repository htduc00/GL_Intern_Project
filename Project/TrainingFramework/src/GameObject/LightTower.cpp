#include "LightTower.h"
#include "ObjectPool.h"
#include "ResourceManagers.h"

LightTower::LightTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
	int damage, int range, int gold): Tower(model,shader,texture,damage,range, gold)
{
}

LightTower::~LightTower()
{
}

void LightTower::Upgrade()
{
	if (m_level == 3) return;
	else if (m_level == 1)
		SetTexture(ResourceManagers::GetInstance()->GetTexture("LightTower2.tga"));
	else if(m_level == 2)
		SetTexture(ResourceManagers::GetInstance()->GetTexture("LightTower3.tga"));
	m_damage *= 1.5;
	m_range += 50;
	m_level += 1;
}

void LightTower::Fire(std::shared_ptr<Enemy> target)
{
	LightBullet* bullet = ObjectPool::GetInstance()->getLightBullet();
	bullet->Set2DPosition(m_position.x, m_position.y-40);
	bullet->SetTarget(target);
	bullet->SetDamage(getDamage());
	bullet->SetSize(16, 16);
	bullet->setNumFrames(4);
	bullet->SetActive(true);
}

