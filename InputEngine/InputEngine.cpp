// InputEngine.cpp : Defines the exported functions for the DLL application.
//

#include "InputEngine.h"

InputEngine::InputEngine()
{
}

void InputEngine::PressKeyUnicode(uint8_t ca, bool bExtended)
{
	//Structure for the keyboard event
	INPUT ip;
	//Set up the INPUT structure
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	//Use Uniceode as the key event
	ip.ki.dwFlags = KEYEVENTF_UNICODE;
	ip.ki.wScan = ca;  //Set a unicode character to use (A)

	SendInput(1, &ip, sizeof(INPUT));

	//Prepare a keyup event
	ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

//The input must be Windows Scancodes
void InputEngine::PressKeyOthers(uint8_t ca, bool bExtended)
{
	//Structure for the keyboard event
	INPUT ip;
	//Set up the INPUT structure
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = ca; //We're doing scan codes instead
	ip.ki.dwExtraInfo = 0;

	//Use Uniceode as the key event
	ip.ki.dwFlags = 0;
	ip.ki.wScan = 0;  //Set a unicode character to use (A)

	SendInput(1, &ip, sizeof(INPUT));

	//Prepare a keyup event
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void InputEngine::MouseMovements(uint8_t dwFlags, uint16_t dx, uint16_t dy, uint8_t mouseData) {

	//Structuring for the mouse event
	INPUT ip;
	//Set up the INPUT structure
	ip.type = INPUT_MOUSE;
	ip.mi.dx = dx;
	ip.mi.dy = dy;
	/**
	* If dwFlags contains MOUSEEVENTF_WHEEL, then mouseData specifies the amount of wheel movement.
	* A positive value indicates that the wheel was rotated forward, away from the user;
	* a negative value indicates that the wheel was rotated backward, toward the user.
	* One wheel click is defined as WHEEL_DELTA, which is 120.
	*
	* If dwFlags does not contain MOUSEEVENTF_WHEEL, MOUSEEVENTF_XDOWN, or MOUSEEVENTF_XUP, then mouseData should be zero.
	*
	* If dwFlags contains MOUSEEVENTF_XDOWN or MOUSEEVENTF_XUP, then mouseData specifies which X buttons were pressed or released.
	* This value may be any combination of the following flags
	**/
	ip.mi.mouseData = mouseData;
	ip.mi.dwFlags = dwFlags;

	SendInput(1, &ip, sizeof(INPUT));

}

uint8_t* InputEngine::getCommandBuffer() {
	return command;
}

void InputEngine::execute() {
	uint8_t inputType = command[0];
	uint8_t actionType = command[1];
	uint8_t dataLength = command[2];

	switch (inputType) {
		//Data is for mouse events
	case INPUT_TYPE_MOUSE:
		switch (actionType) {
		case MOUSE_ACTION_LEFT_CLICK:
			std::cout << "CLICKLCICKCLICK left click" << std::endl;
			break;
		case MOUSE_ACTION_RIGHT_CLICK:
			std::cout << "CLICKLCICKCLICK right click" << std::endl;
			break;
		case MOUSE_ACTION_LEFT_DOWN:
			std::cout << "CLICKLCICKCLICK left down" << std::endl;
			break;
		case MOUSE_ACTION_LEFT_UP:
			std::cout << "CLICKLCICKCLICK left up" << std::endl;
			break;
		case MOUSE_ACTION_MIDDLE_CLICK:
			std::cout << "CLICKLCICKCLICK middle click" << std::endl;
			break;
		case MOUSE_ACTION_MOVE:
			if (dataLength == 4) {
				//MouseMovements(0, (command[3] << 8) + command[4], (command[5] << 8) + command[6], 0);
				//printf("Received coordinate %d,%d \n", (command[3] << 8) + command[4], (command[5] << 8) + command[6]);
				printf("Received coordinate\n");
				//std::cout << "move" << command[3] << " " << command[4];
				break;
			}

		case MOUSE_ACTION_SCROLL:
			if (dataLength == 2) {
				break;
			}
		}
		//Data is for keyboard events
	case INPUT_TYPE_KEYBOARD:
		switch (actionType) {
		case KEYBOARD_ACTION_EMOJI:
			break;
		case KEYBOARD_ACTION_KEYCHAR:
			PressKeyUnicode(command[3], true);
			break;
		case KEYBOARD_ACTION_META:
			break;
		case KEYBOARD_ACTION_OTHERS:
			PressKeyOthers(command[3], true);
			break;
		};
	};
};
