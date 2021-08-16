#include "BaseObject.h"
#include <iostream>
BaseObject::BaseObject()
{
	this->id = "";
	this->name = "";
	this->pos = {0,0};
}

BaseObject::~BaseObject(){}

BaseObject::BaseObject(std::string id, std::string name, Pos pos) {
	this->id = id;
	this->name = name;
	this->pos = pos;
}

Pos BaseObject::getPos() {
	return this->pos;
}

void BaseObject::setPos(Pos pos) {
	this->pos = pos;
}

 void BaseObject::printPos() {
	 std::cout << this->name<<":  (" << this->pos.x << "," << this->pos.y << ")" << std::endl;
}

std::string BaseObject::getName() {
	return this->name;
}
