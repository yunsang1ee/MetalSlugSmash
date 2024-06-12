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
			EFFECT,
			PlayerSound
		};



		void LoadSound(const std::wstring& name, const std::string& soundPath);
		void playSound(const std::wstring& soundName, SoundManager::SoundType type,const bool paused=false);

		FMOD::Channel* GetBackGroundChannel() { return BackGroundchannel; }
		FMOD::Channel* GetplayerSound() { return playerSound; }
		static SoundManager* GetInstance();
		static void Release();


	private:
		static SoundManager* instance;
		std::map<std::wstring, FMOD::Sound*> sounds;
		
		FMOD::System* system;
		FMOD::Channel* BackGroundchannel;//채널 만들거면 채널 포인터로 추가하기
		FMOD::Channel* playerSound;
		FMOD_RESULT result;
	};
}

