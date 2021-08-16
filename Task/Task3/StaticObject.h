#pragma once
#include "BaseObject.h"

class StaticObject : public BaseObject
{
public:
	StaticObject();
	StaticObject(std::string id, std::string name, Pos pos);
	virtual ~StaticObject();
	void move(int v_x, int v_y) override;
};