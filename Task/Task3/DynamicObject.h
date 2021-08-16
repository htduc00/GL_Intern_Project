#pragma once
#include "BaseObject.h"

class DynamicObject : public BaseObject 
{
public:
	DynamicObject();
	DynamicObject(std::string id, std::string name, Pos pos);
	virtual ~DynamicObject();
	void move(int v_x, int v_y);
};
