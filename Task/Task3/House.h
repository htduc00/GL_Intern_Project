#pragma once
#include "StaticObject.h"

class House : public StaticObject
{
public:
	House();
	House(std::string id, std::string name, Pos pos);
	~House();
};