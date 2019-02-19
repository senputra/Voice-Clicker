#ifndef INPUT_ENGINE_H
#define INPUT_ENGINE_H

#ifdef INPUTENGINE_EXPORTS
#define INPUTENGINE_API __declspec(dllexport) 
#else  
#define INPUTENGINE_API __declspec(dllimport) 
#endif  

#include <Windows.h>
#include <iostream>
#include <stdint.h>


class INPUTENGINE_API InputEngine {
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
	InputEngine();

	void static PressKeyUnicode(uint8_t ca, bool bExtended);

	//The input must be Windows Scancodes
	void static PressKeyOthers(uint8_t ca, bool bExtended);

	void static MouseMovements(uint8_t dwFlags, uint16_t dx, uint16_t dy, uint8_t mouseData);

	uint8_t* getCommandBuffer();

	void execute();
};

#endif