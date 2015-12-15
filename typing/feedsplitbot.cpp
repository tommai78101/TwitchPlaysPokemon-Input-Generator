/*

AGAR.IO FeedSplit Automation Bot

=====================================

For use only with this private server:

http://agar.io/?ip=vps56296.vps.ovh.ca:443

Other servers allowing you to self-feed yourself and/or
instant merge is also applicable.

=====================================

CONTROLS:

Q: Toggle Constant Feeding.
E: Toggle Constant Splitting.
Z: Quit Application.


*/

#include <Windows.h>
#include <iostream>

void GenerateKey(short vk, bool extended){
	KEYBDINPUT keyboardInput = {};
	INPUT input = {};

	//Key down.
	if (extended){
		keyboardInput.dwFlags = KEYEVENTF_EXTENDEDKEY;
	}
	keyboardInput.wVk = vk;
	input.type = INPUT_KEYBOARD;
	input.ki = keyboardInput;
	SendInput(1, &input, sizeof(INPUT));

	//Key up.
	keyboardInput = {};
	input = {};
	keyboardInput.dwFlags = KEYEVENTF_KEYUP;
	if (extended){
		keyboardInput.dwFlags |= KEYEVENTF_EXTENDEDKEY;
	}
	keyboardInput.wVk = vk;
	input.type = INPUT_KEYBOARD;
	input.ki = keyboardInput;
	SendInput(1, &input, sizeof(INPUT));
	return;
}

int main(){
	bool feedFlag = false;
	bool splitFlag = false;
	bool quitFlag = false;
	HKL keyboardLayout = GetKeyboardLayout(0);
	while (!quitFlag){
		if (GetKeyState(VkKeyScanEx('q', keyboardLayout)) & 0x8000){
			feedFlag = !feedFlag;
			system("cls");
			std::cout << "Feed Flag: " << ((feedFlag) ? "TRUE" : "FALSE") << "    Split Flag: " << ((splitFlag) ? "TRUE" : "FALSE") << std::endl; 
			Sleep(200);
		}
		else if (GetKeyState(VkKeyScanEx('e', keyboardLayout)) & 0x8000) {
			splitFlag = !splitFlag;
			system("cls");
			std::cout << "Feed Flag: " << ((feedFlag) ? "TRUE" : "FALSE") << "    Split Flag: " << ((splitFlag) ? "TRUE" : "FALSE") << std::endl;
			Sleep(200);
		}
		else if (GetKeyState(VkKeyScanEx('z', keyboardLayout)) & 0x8000) {
			quitFlag = true;
			Sleep(200);
			continue;
		}

		if (feedFlag){
			GenerateKey(VkKeyScanEx('w', keyboardLayout), false);
			Sleep(50);
		}
		if (splitFlag){
			GenerateKey(VkKeyScanEx(' ', keyboardLayout), false);
			Sleep(50);
		}
	}
	return 0;
}