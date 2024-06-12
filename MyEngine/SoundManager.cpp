#include "SoundManager.h"
using namespace ys;
SoundManager* SoundManager::instance = nullptr;

void SoundManager::LoadSound(const std::wstring& name,const std::string& soundPath)
{
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		MessageBox(NULL, L"FMOD error! System_Create", L"ERROR", MB_OK);
		return;
	}
	system->init(32, FMOD_INIT_NORMAL, 0);
	
	FMOD::Sound* sound = nullptr;

	system->createSound(soundPath.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
	if (sound == nullptr)
	{
		MessageBox(NULL, L"Sound not found", L"ERROR", MB_OK);
		return;
	}
	
	

	auto iter = sounds.find(name);
	if(iter==sounds.end()) {
		sounds.insert(std::make_pair(name, sound));
	}
	else {
		MessageBox(NULL, L"Sound name already exists", L"ERROR", MB_OK);
		return;
	}
	
}



void SoundManager::playSound(const std::wstring& soundName,SoundManager::SoundType type,const bool paused )
{
	
	
	auto iter = sounds.find(soundName);
	if (iter == sounds.end())
	{
		MessageBox(NULL, L"Sound not found", L"ERROR", MB_OK);
		return;
	}
	switch (type)
	{
	case SoundManager::SoundType::BACKGROUND:
		system->playSound(iter->second, 0, paused, &BackGroundchannel);
		break;
	case SoundManager::SoundType::PlayerSound:
		system->playSound(iter->second, 0, paused, &playerSound);
		break;
	default:
		break;
	}
	
}

SoundManager* SoundManager::GetInstance()
{
	
	if (instance == nullptr)
		instance = new SoundManager();
	return instance;
	
}

void SoundManager::Release()
{
	
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
	
}
