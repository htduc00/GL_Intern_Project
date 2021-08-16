#include "Car.h"
Car::Car() : DynamicObject() {}
Car::Car(std::string id, std::string name, Pos pos) : DynamicObject(id, name, pos) {}
Car::~Car() {}
