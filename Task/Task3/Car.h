#pragma once
#include "DynamicObject.h"

class Car : public DynamicObject
{
public:
	Car();
	Car(std::string id, std::string name, Pos pos);
	~Car();
};