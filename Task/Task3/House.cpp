#include"House.h"

House::House() : StaticObject (){}
House::House(std::string id, std::string name, Pos pos) : StaticObject(id, name, pos) {}
House::~House(){}