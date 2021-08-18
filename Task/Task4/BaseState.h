#pragma once
class StateContext;
class BaseState {
public:
	virtual void unlock(StateContext* context) = 0;
	virtual void open(StateContext* context) = 0;
	virtual void close(StateContext* context) = 0;
	virtual void lock(StateContext* context) = 0;
};