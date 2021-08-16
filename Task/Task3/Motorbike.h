#pragma once
#include "DynamicObject.h"

class Motorbike : public DynamicObject
{
public:
	Motorbike();
	Motorbike(std::string id, std::string name, Pos pos);
	~Motorbike();
};