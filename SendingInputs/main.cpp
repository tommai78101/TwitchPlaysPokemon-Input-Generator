#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

//Converting chars to virtual codes
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
		short vk = VkKeyScanEx(str[i], layout);
		GenerateKey(vk, false);
		Sleep(100);
	}
	GenerateKey(VK_RETURN, false);
}

void main(){
	srand(time(0));
	int r_old = -1, r = -2;
	bool flag = false;
	while (true){
		//***   PLEASE CHANGE THIS TO WHATEVER FAVORITE BROWSER YOU ARE USING.
		//***   ALSO PLEASE MODIFY THE STRING VALUE IF THE TITLE OF YOUR TAB IS WRONG.
		//HWND window = FindWindow(0, "TwitchPlaysPokemon - Twitch - Google Chrome");
		//HWND window = FindWindow(0, "TwitchPlaysPokemon - Twitch - Mozilla Firefox");
		HWND window = FindWindow(0, "TwitchPlaysPokemon - Twitch - Internet Explorer");
		if (window){
			SetForegroundWindow(window);
			SetFocus(window);
		}
		while (r == r_old){
			r = rand() % 3;
		}
		switch (r){
			case 0:{
				GenerateStrings("right", 5);
				break;
			}
			case 1:{
				GenerateStrings("up", 2);
				break;
			}
			case 2:{
				GenerateStrings("a", 1);
				break;
			}
			case 3:{
				GenerateStrings("left", 4);
				break;
			}
			case 4:{
				GenerateStrings("down", 4);
				break;
			}
			case 5:{
				GenerateStrings("b", 1);
				break;
			}
		}
		r_old = r;
		Sleep(5015 + ((r + 3) * 5));
	}
}