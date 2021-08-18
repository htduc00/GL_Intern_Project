#include "ClosedState.h"
#include "OpenedState.h"
#include"StateContext.h"
#include <iostream>

void OpenedState::unlock(StateContext* context) {
	std::cout << "Door is already unlock and opened\n" << std::endl;
}
void OpenedState::open(StateContext* context) {
	std::cout << "Door is already opened\n" << std::endl;
}
void OpenedState::close(StateContext* context) {
	std::cout << "State: opened -> closed\n" << std::endl;
	context->setState(new ClosedState());
}
void OpenedState::lock(StateContext* context) {
	std::cout << "Door is opened, can't lock\n" << std::endl;
}