#pragma once


#ifndef INPUT_ENGINE_H
#define INPUT_ENGINE_H

#include <Windows.h>
#include <iostream>

class InputEngine {
private:
	uint8_t *command = new uint8_t[8];

	static const uint8_t INPUT_TYPE_KEYBOARD = 0;
	static const uint8_t INPUT_TYPE_MOUSE = 1;
	static const uint8_t MOUSE_ACTION_LEFT_CLICK = 2;
	static const uint8_t MOUSE_ACTION_RIGHT_CLICK = 3;
	static const uint8_t MOUSE_ACTION_MIDDLE_CLICK = 4;
	static const uint8_t MOUSE_ACTION_MOVE = 5;
	static const uint8_t MOUSE_ACTION_SCROLL = 6;
	static const uint8_t MOUSE_ACTION_LEFT_DOWN = 7;
	static const uint8_t MOUSE_ACTION_LEFT_UP = 8;
	static const uint8_t KEYBOARD_ACTION_KEYCHAR = 9;
	static const uint8_t KEYBOARD_ACTION_META = 10;
	static const uint8_t KEYBOARD_ACTION_EMOJI = 11;
	static const uint8_t KEYBOARD_ACTION_OTHERS = 12;

public:
	void static PressKeyUnicode(uint8_t ca, BOOL bExtended)
	{
		//Structure for the keyboard event
		INPUT ip;
		//Set up the INPUT structure
		ip.type = INPUT_KEYBOARD;
		ip.ki.time = 0;
		ip.ki.wVk = 0; //We're doing scan codes instead
		ip.ki.dwExtraInfo = 0;

		//Use Uniceode as the key event
		ip.ki.dwFlags = KEYEVENTF_UNICODE;
		ip.ki.wScan = ca;  //Set a unicode character to use (A)

		SendInput(1, &ip, sizeof(INPUT));

		//Prepare a keyup event
		ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
	}

	void static PressKeyOthers(uint8_t ca, BOOL bExtended)
	{
		//Structure for the keyboard event
		INPUT ip;
		//Set up the INPUT structure
		ip.type = INPUT_KEYBOARD;
		ip.ki.time = 0;
		ip.ki.wVk = 0; //We're doing scan codes instead
		ip.ki.dwExtraInfo = 0;

		//Use Uniceode as the key event
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = ca;  //Set a unicode character to use (A)

		SendInput(1, &ip, sizeof(INPUT));

		//Prepare a keyup event
		ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
	}

	uint8_t* getCommandBuffer() {
		return command;
	}

	void execute() {
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
				if (dataLength == 2) {
					std::cout << "move" << command[3] << " " << command[4];
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
};

#endif