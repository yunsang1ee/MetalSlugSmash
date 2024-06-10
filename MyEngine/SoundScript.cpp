#include"SoundScript.h"

void SoundScript::soundLoad(std::wstring soundName)
{
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		MessageBox(NULL, L"FMOD error! System_Create", L"ERROR", MB_OK);
		return;
	}
	system->init(32, FMOD_INIT_NORMAL, 0);
	std::string name;
	name.assign(soundName.begin(), soundName.end());
	system->createSound(name.c_str(),FMOD_LOOP_NORMAL, 0, &sound);
}

void SoundScript::playSound(std::wstring soundName)
{
	
	channel->stop();
	channel->setVolume(0.5f);
	system->playSound(sound, 0, false, &channel);
	

}
