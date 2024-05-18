#pragma once
#include "CommonInclude.h"

//#include <Windows.h>
//#include <vector>
//#include <string>
//#include <map>
//#include <utility>

namespace ys
{
	enum class Key : BYTE
	{
		Num0 = 0x30, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, 
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		Colons = 0xBA
	};

	using KeyState = BYTE;
	constexpr KeyState kKeyDownBit = 1;
	constexpr KeyState kKeyPressedBit = 2;
	constexpr KeyState kKeyUpBit = 4;

	class InputManager
	{
	public:
		
		static void Init();//메세지 루프 이전에 필수사용
		static void BeforeUpdate();//메인 업데이트 이전 키 업데이트
		static void AfterUpdate();//메인 업데이트 이후 키 업데이트
	
		static void setKeyState(WORD code, bool isPressed, bool isUp);
		//static math::Vector2 getMousePosition();

		inline static bool getKeyDown(UINT code) { return  (keys[static_cast<UINT>(code)] & kKeyDownBit) != 0; }
		inline static bool getKey(UINT code) { return  (keys[static_cast<UINT>(code)] & kKeyPressedBit) != 0; }
		inline static bool getKeyUp(UINT code) { return  (keys[static_cast<UINT>(code)] & kKeyUpBit); }

		inline static KeyState getKeyState(UINT code) { return  keys[static_cast<UINT>(code)]; }
	private:
		static std::vector<KeyState> keys;
		//static math::Vector2 mousePosition;
	};
}