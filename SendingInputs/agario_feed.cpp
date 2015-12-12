#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

//Placed here for easy access.
static HKL layout = GetKeyboardLayout(0);


void GenerateKey(int vk, bool extended){
	KEYBDINPUT keyboard = {};
	INPUT input = {};

	//Key down
	if (extended){
		keyboard.dwFlags = KEYEVENTF_EXTENDEDKEY;
	}
	keyboard.wVk = vk;
	input.type = INPUT_KEYBOARD;
	input.ki = keyboard;
	SendInput(1, &input, sizeof(input));

	//Key up
	keyboard = {};
	input = {};
	keyboard.dwFlags = KEYEVENTF_KEYUP;
	if (extended){
		keyboard.dwFlags |= KEYEVENTF_EXTENDEDKEY;
	}
	keyboard.wVk = vk;
	input.type = INPUT_KEYBOARD;
	input.ki = keyboard;
	SendInput(1, &input, sizeof(input));
	return;
}


void GenerateStrings(char* str, int size){
	for (int i = 0; i < size; i++){
		//Converting chars to virtual codes
		short vk = VkKeyScanEx(str[i], layout);
		GenerateKey(vk, false);
		//Required for more authentic feel.
		Sleep(100);
	}
	GenerateKey(VK_RETURN, false);
}

void main(){
	srand(static_cast<unsigned int>(time(0)));
	bool flag = false;
	while (true){
		/*
		------------------------------------------------------------------------------------
		***   PLEASE CHANGE THIS TO WHATEVER FAVORITE BROWSER YOU ARE USING.             ***
		***   ALSO PLEASE MODIFY THE STRING VALUE IF THE TITLE OF YOUR TAB IS WRONG.     ***
		------------------------------------------------------------------------------------
		HWND window = FindWindow(0, "TwitchPlaysPokemon - Twitch - Google Chrome");
		HWND window = FindWindow(0, "TwitchPlaysPokemon - Twitch - Mozilla Firefox");

		AND REPLACE THE DEFAULT LINE OF CODE.
		*/

		//Default: For IE11. Not IE8, IE9, and definitely not IE10.
		HWND window = FindWindow(0, "Agar.io");
		//

		if (window){
			//This keeps the livestream focused and ready for input.
			SetForegroundWindow(window);
			SetFocus(window);
		}

		if (GetKeyState(VkKeyScanEx('q', layout)) & 0x8000){
			flag = !flag;
			std::cout << "Pressed Q - New State: " << (flag ? "TRUE" : "FALSE") << std::endl;
		}

		if (flag){
			GenerateKey(VkKeyScanEx('w', layout), false);
		}

		//MODIFY THE VALUE "5" TO THE SLOW TEXT TIME.
		//EXAMPLE: IF SLOW MODE IS 5 seconds PER MESSAGE, THE VALUE IS 5.

		//YOU MAY CLOSE THE BOT AT ANY POINT IN TIME. JUST BE AWARE THAT 
		//THE BOT USES KEY PRESSES AS IF YOU ARE PRESSING ON THE KEYS.
		//HOTKEYS CAN BE TRIGGERED IF NOT CAREFUL!!
	}
}