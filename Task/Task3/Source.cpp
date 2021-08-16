#include<iostream>
#include<vector>
#include "Car.h"
#include "Motorbike.h"
#include "Tree.h"
#include "House.h"

int main() {
	std::vector<BaseObject*> listObj;

	BaseObject* car = new Car("C1203", "Mercedes-Benz", {0,4});
	BaseObject* motorbike = new Motorbike("M2063", "Thunderbolt", {2,2});
	BaseObject* tree = new Tree("T6203", "Sunflower", {5,3});
	BaseObject* house = new House("H0931", "House", {7,10});
	listObj.push_back(car);
	listObj.push_back(motorbike);
	listObj.push_back(tree);
	listObj.push_back(house);

	std::cout << "-------Name---------" << std::endl;
	for (auto obj : listObj) {
		std::cout << obj->getName() << std::endl;
	}
	std::cout << "\n-------Position before move--------" << std::endl;
	for (auto obj : listObj) {
		obj->printPos();
	}
	std::cout << "\n-------Moving--------" << std::endl;
	for (auto obj : listObj) {
		obj->move(10, 10);
	}
	std::cout << "\n------- Position after move--------" << std::endl;
	for (auto obj : listObj) {
		obj->printPos();
	}

}