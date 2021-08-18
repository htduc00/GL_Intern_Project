#include "ClosedState.h"
#include "OpenedState.h"
#include "LockedState.h"
#include"StateContext.h"
#include <iostream>
void ClosedState::unlock(StateContext* context) {
	std::cout << "Door is already unlock\n" << std::endl;
}
void ClosedState::open(StateContext* context) {
	std::cout << "State: closed -> opened\n" << std::endl;
	context->setState(new OpenedState());
}
void ClosedState::close(StateContext* context) {
	std::cout << "Door is already closed\n" << std::endl;
}
void ClosedState::lock(StateContext* context) {
	std::cout << "State: closed -> locked\n" << std::endl;
	context->setState(new LockedState());
}