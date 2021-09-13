#pragma once
#include <list>
#include "LightBullet.h"
#include "MagicBullet.h"
#include "MoonBullet.h"
#include "Singleton.h"

class ObjectPool :public CSingleton<ObjectPool>
{
private:
    std::list<LightBullet*> listLightBullet;
    std::list<MagicBullet*> listMagicBullet;
    std::list<MoonBullet*> listMoonBullet;
public:
    ObjectPool();
    LightBullet* getLightBullet();
    MagicBullet* getMagicBullet();
    MoonBullet* getMoonBullet();
    void returnLightBullet(LightBullet* object);
    void returnMagicBullet(MagicBullet* object);
    void returnMoonBullet(MoonBullet* object);

    std::list<LightBullet*> getListLightBullet();
    std::list<MagicBullet*> getListMagicBullet();
    std::list<MoonBullet*> getListMoonBullet();
};