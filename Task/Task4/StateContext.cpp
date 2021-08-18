#include "StateContext.h"

StateContext::StateContext(BaseState* state) : m_state(nullptr)
{
	this->setState(state);
}

StateContext::~StateContext() {
	delete this->m_state;
}

void StateContext::setState(BaseState* state){
	if (this->m_state != nullptr)
		delete this->m_state;
	this->m_state = state;
}
void StateContext::unlockDoor() {
	this->m_state->unlock(this);
}
void StateContext::openDoor() {
	this->m_state->open(this);
}
void StateContext::closeDoor() {
	this->m_state->close(this);
}
void StateContext::lockDoor() {
	this->m_state->lock(this);
}
