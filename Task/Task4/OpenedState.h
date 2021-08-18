#pragma once
#include "BaseState.h"
class OpenedState : public BaseState {
public:
	void unlock(StateContext* context);
	void open(StateContext* context);
	void close(StateContext* context);
	void lock(StateContext* context);
};