#pragma once
#include<string>
struct Pos{
	int x;
	int y;
};

class BaseObject {
private:
	std::string id;
	std::string name;
	Pos pos;
public:
	BaseObject();
	BaseObject(std::string id, std::string name, Pos pos);
	virtual ~BaseObject();
	std::string getName();
	virtual void move(int v_x, int v_y) = 0;
	void printPos();
	Pos getPos();
	void setPos(Pos pos);
};