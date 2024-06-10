#include "SoundManager.h"
using namespace ys;
SoundManager* SoundManager::instance = nullptr;

void SoundManager::LoadSound(const std::wstring& name,const std::wstring& soundPath)
{
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		MessageBox(NULL, L"FMOD error! System_Create", L"ERROR", MB_OK);
		return;
	}
	system->init(32, FMOD_INIT_NORMAL, 0);
	std::string _path;
	_path.assign(soundPath.begin(), soundPath.end());
	FMOD::Sound* sound = nullptr;

	system->createSound(_path.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
	if (sound == nullptr)
	{
		MessageBox(NULL, L"Sound not found", L"ERROR", MB_OK);
		return;
	}
	sounds.insert(std::make_pair(soundPath, sound));

	auto iter = names.find(soundPath);
	if (iter == names.end())
	{
		names.insert(std::make_pair(name, soundPath));
	}
	else {
		MessageBox(NULL, L"Sound name already exists", L"ERROR", MB_OK);
		return;
	}
	
}



void SoundManager::playSound(const std::wstring& soundName,SoundManager::SoundType type )
{
	auto _path = names.find(soundName);
	if (_path == names.end())
	{
		return;
	}
	
	auto iter = sounds.find(_path->second);
	if (iter == sounds.end())
	{
		MessageBox(NULL, L"Sound not found", L"ERROR", MB_OK);
		return;
	}
	switch (type)
	{
	case SoundManager::SoundType::BACKGROUND:
		system->playSound(iter->second, 0, false, &BackGroundchannel);
		break;
	case SoundManager::SoundType::EFFECT:
		system->playSound(iter->second, 0, false, &Effectchannel);
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
