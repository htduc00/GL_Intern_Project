#include "ObjectPool.h"
#include "ResourceManagers.h"

ObjectPool::ObjectPool()
{
    auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
    auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
    auto lightBulletTexture = ResourceManagers::GetInstance()->GetTexture("LightBullet.tga");
    auto magicBulletTexture = ResourceManagers::GetInstance()->GetTexture("MagicBullet1.tga");
    auto moonBulletTexture = ResourceManagers::GetInstance()->GetTexture("MoonBullet1.tga");
    for (int i = 0; i < 10; i++) {
        LightBullet* lightBullet = new LightBullet(model, shader, lightBulletTexture, 0, 300.0f);
        MagicBullet* magicBullet = new MagicBullet(model, shader, magicBulletTexture, 0, 300.0f);
        MoonBullet* moonBullet = new MoonBullet(model, shader, moonBulletTexture, 0, 300.0f);

        listLightBullet.push_back(lightBullet);
        listMagicBullet.push_back(magicBullet);
        listMoonBullet.push_back(moonBullet);
    }
}

LightBullet* ObjectPool::getLightBullet()
{
    LightBullet* bullet = listLightBullet.front();
    if (bullet->GetActive()) {
        auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
        auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
        auto texture = ResourceManagers::GetInstance()->GetTexture("LightBullet.tga");
        bullet = new LightBullet(model, shader, texture, 0, 300.0f);
        listLightBullet.push_back(bullet);
        return bullet;
    }
    listLightBullet.pop_front();
    listLightBullet.push_back(bullet);
    return bullet;
}
MagicBullet* ObjectPool::getMagicBullet()
{
    MagicBullet* bullet = listMagicBullet.front();
    if (bullet->GetActive()) {
        auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
        auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
        auto texture = ResourceManagers::GetInstance()->GetTexture("MagicBullet1.tga");
        bullet = new MagicBullet(model, shader, texture, 0, 300.0f);
        listMagicBullet.push_back(bullet);
        return bullet;
    }
    listMagicBullet.pop_front();
    listMagicBullet.push_back(bullet);
    return bullet;
}
MoonBullet* ObjectPool::getMoonBullet()
{
    MoonBullet* bullet = listMoonBullet.front();
    if (bullet->GetActive()) {
        auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
        auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
        auto texture = ResourceManagers::GetInstance()->GetTexture("MoonBullet1.tga");
        bullet = new MoonBullet(model, shader, texture, 0, 300.0f);
        listMoonBullet.push_back(bullet);
        return bullet;
    }
    listMoonBullet.pop_front();
    listMoonBullet.push_back(bullet);
    return bullet;
}
void ObjectPool::returnLightBullet(LightBullet* object)
{
    listLightBullet.push_back(object);
}
void ObjectPool::returnMagicBullet(MagicBullet* object)
{
    listMagicBullet.push_back(object);
}
void ObjectPool::returnMoonBullet(MoonBullet* object)
{
    listMoonBullet.push_back(object);
}

std::list<LightBullet*> ObjectPool::getListLightBullet() {
    return listLightBullet;
}
std::list<MagicBullet*> ObjectPool::getListMagicBullet() {
    return listMagicBullet;
}
std::list<MoonBullet*> ObjectPool::getListMoonBullet() {
    return listMoonBullet;
}