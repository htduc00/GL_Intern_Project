#include "StateContext.h"
#include "ClosedState.h"
#include "LockedState.h"
#include "OpenedState.h"
#include <iostream>
#include <crtdbg.h>

int main() 
{
	StateContext* context = new StateContext(new ClosedState());
	std::cout << "State: closed" << std::endl;
	std::cout << "Unlock Door" << std::endl;
	context->unlockDoor();
	std::cout << "Open Door" << std::endl;
	context->openDoor();
	std::cout << "Close Door" << std::endl;
	context->closeDoor();
	std::cout << "Lock Door" << std::endl;
	context->lockDoor();

	delete context;
	_CrtDumpMemoryLeaks();
	return 0;
}