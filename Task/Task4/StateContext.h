#pragma once
#include "BaseState.h"
class StateContext {
private:
	BaseState* m_state;
public:
	StateContext(BaseState* state);
	virtual ~StateContext();
	void setState(BaseState* state);
	void unlockDoor();
	void openDoor();
	void closeDoor();
	void lockDoor();
};