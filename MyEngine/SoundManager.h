#pragma once
#include <Windows.h>
#include <string>
#include <vector>

#include "fmod.hpp"
#include "fmod_errors.h"
#include <map>
namespace ys
{
	class SoundManager
	{
	public:
		enum class SoundType
		{
			BACKGROUND,
			EFFECT
		};



		void LoadSound(const std::wstring& name, const std::wstring& soundPath);
		void playSound(const std::wstring& soundName, SoundManager::SoundType type);


		static SoundManager* GetInstance();
		static void Release();


	private:
		static SoundManager* instance;
		std::map<std::wstring, FMOD::Sound*> sounds;
		std::map<std::wstring, std::wstring> names;
		FMOD::System* system;
		FMOD::Channel* BackGroundchannel;//채널 만들거면 채널 포인터로 추가하기
		FMOD::Channel* Effectchannel;
		FMOD_RESULT result;
	};
}

