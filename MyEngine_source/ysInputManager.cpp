#include "ysInputManager.h"

namespace ys
{
	constexpr WORD kKeyDataSize = 512;//Alt���� ����
	//Ctrl�� Ctrl + Alt���� �����ϸ� 2048����
	std::vector<KeyState> InputManager::keys;

	void InputManager::Init()
	{
		keys.assign(kKeyDataSize, 0x00);
	}

	void InputManager::BeforeUpdate()
	{//���� KF_ALTDOWN�� �̿��� bool�� parameter�� �޾Ƽ� AltŰ ���ձ��� ��������
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