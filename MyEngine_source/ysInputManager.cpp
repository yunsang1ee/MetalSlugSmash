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
/*
서버도 데이터처리 1억
클라이언트	/	서버(*자료구조*, 알고리즘)	/	그래픽스(*자료구조*, 알고리즘)	/	엔진
클라, 엔진 프로그래머(툴 제작)---┐
	안주거	<----------	그래픽스 프로그래머(눈에 바로보여)(기본적인 미적감각)
							-> 테크니컬 아티스트(얘가 게임업계의 꽃(돈도 제일 많이 줌))
						서버는 그나마 디버깅툴이 있어
						그래픽스? 그냥 디버그가 없어
1억개의 폴리곤을 15마이크로 최적화기술(삼각함수, 셰이더를 만들기위한 기본 선형대수학, 3D표현, 물리)
(X)수학 -> 수학잘하네? -> 그래픽스
(O)기본적인 수학지식(대학에서 배우는 수준) -> 그래픽스 -> 그냥 박치기해 -> 수학을 공부해
*/