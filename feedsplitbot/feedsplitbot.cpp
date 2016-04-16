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
TILDE: Toggle Enable/Disable Bot.

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
	system("cls");
	std::cout << "Press \"Q\" to enable auto-eject mass. " << std::endl;
	std::cout << "Press \"E\" to enable auto-split. " << std::endl;
	std::cout << "Press \"Z\" to quit. " << std::endl;
	bool feedFlag = false;
	bool splitFlag = false;
	bool quitFlag = false;
	bool disableFlag = false;
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
			continue;
		}
		else if (GetKeyState(VkKeyScanEx('`', keyboardLayout)) & 0x8000) {
			disableFlag = !disableFlag;
			feedFlag = splitFlag = false;
			system("cls");
			if (disableFlag){
				std::cout << "Disabled." << std::endl;
			}
			else {
				std::cout << "Feed Flag: " << ((feedFlag) ? "TRUE" : "FALSE") << "    Split Flag: " << ((splitFlag) ? "TRUE" : "FALSE") << std::endl;
			}
			Sleep(200);
		}

		if (!disableFlag){
			if (feedFlag){
				GenerateKey(VkKeyScanEx('w', keyboardLayout), false);
				Sleep(50);
			}
			if (splitFlag){
				GenerateKey(VkKeyScanEx(' ', keyboardLayout), false);
				Sleep(50);
			}
		}
		else {
			Sleep(1);
		}
	}
	return 0;
}