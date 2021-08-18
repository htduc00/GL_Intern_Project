#include "LockedState.h"
#include "ClosedState.h"
#include <iostream>
void LockedState::unlock(StateContext* context) {
	std::cout << "State: locked -> closed\n" << std::endl;
	context->setState(new ClosedState());
}
void LockedState::open(StateContext* context) {
	std::cout << "Door is locked, can't open\n" << std::endl;
}
void LockedState::close(StateContext* context) {
	std::cout << "Door is already closed and locked\n" << std::endl;
}
void LockedState::lock(StateContext* context) {
	std::cout << "Door is already locked\n" << std::endl;
}