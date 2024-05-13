#include "ysInputManager.h"

namespace ys
{
	constexpr WORD kKeyDataSize = 512;//Alt조합 상정
	//Ctrl과 Ctrl + Alt까지 상정하면 2048까지
	std::vector<KeyState> InputManager::keys;

	void InputManager::Init()
	{
		keys.assign(kKeyDataSize, 0x00);
	}

	void InputManager::BeforeUpdate()
	{//이후 KF_ALTDOWN을 이용한 bool을 parameter로 받아서 Alt키 조합까지 구현가능
		// &= ~ XOR
		for (WORD keyIndex = 0; keyIndex < kKeyDataSize; ++keyIndex)
		{
			if (getKeyDown(keyIndex))
				keys[keyIndex] |= kKeyPressedBit;
			if (getKeyUp(keyIndex)) {
				keys[keyIndex] &= (~kKeyPressedBit);
			}
		}
	}

	void InputManager::AfterUpdate()
	{
		for (WORD keyIndex = 0; keyIndex < kKeyDataSize; ++keyIndex)
		{
			if (getKeyDown(keyIndex))
				keys[keyIndex] &= (~kKeyDownBit);
			if (getKeyUp(keyIndex))
			{
				keys[keyIndex] &= (~kKeyPressedBit);
				keys[keyIndex] &= (~kKeyUpBit);
			}
		}
	}

	void InputManager::setKeyState(WORD code, bool isPressed, bool isUp)
	{
		if (isPressed)
		{
			if (isUp)
				keys[code] |= kKeyUpBit;
			else
				keys[code] |= kKeyPressedBit;
		}
		else
		{
			if (isUp)
				keys[code] |= kKeyUpBit;
			else
				keys[code] |= kKeyDownBit;
		}
	}
}