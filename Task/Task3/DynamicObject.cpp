#include "DynamicObject.h"
#include<iostream>
DynamicObject::DynamicObject() : BaseObject() {}
DynamicObject::DynamicObject(std::string id, std::string name, Pos pos) : BaseObject(id,name,pos){}
DynamicObject::~DynamicObject(){}

void DynamicObject::move(int v_x, int v_y) {
	std::cout << this->getName() << " is moving..." << std::endl;
	Pos pos = this->getPos();
	pos.x += v_x;
	pos.y += v_y;
	this->setPos(pos);
}