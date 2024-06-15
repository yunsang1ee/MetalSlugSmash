#include "ysSoundManager.h"
#include "ysAudioClip.h"
#include "YSapplication.h"

extern ys::Application app;
namespace ys
{
	std::unordered_multimap<enums::AudioGroup, AudioClip*> SoundManager::groups;
	FMOD::Studio::System* SoundManager::system;
	FMOD::System* SoundManager::coreSystem;

	void SoundManager::Init()
	{
		void* extraDriverData = nullptr;
		FMOD::Studio::System::create(&system);

		system->getCoreSystem(&coreSystem);
		coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);

		system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
	}

	bool SoundManager::CreateSound(const std::string& path, FMOD::Sound** sound)
	{
		if (FMOD_OK != coreSystem->createSound(path.c_str(), FMOD_2D, 0, sound))
			return false;
		return true;
	}

	void SoundManager::SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel)
	{
		coreSystem->playSound(sound, 0, false, channel);
	}
	void SoundManager::SetListenerAttributes(const math::Vector2& pos)
	{
		auto nomalizePosition = pos / app.getScreenf();
		FMOD_VECTOR fmodPos(nomalizePosition.x, nomalizePosition.y, 0.3f);
		FMOD_VECTOR fmodVel(0.0f, 0.0f, 0.0f);
		FMOD_VECTOR fmodForward(0.0f, 0.0f, 1.0f);
		FMOD_VECTOR fmodUp(0.0f, 1.0f, 0.0f);

		coreSystem->set3DListenerAttributes(0, &fmodPos, &fmodVel, &fmodForward, &fmodUp);
	}
	void SoundManager::SetVolume(const float& percent, const enums::AudioGroup& group)
	{
		auto range = groups.equal_range(group);
		for (auto iter = range.first; iter != range.second; ++iter)
			iter->second->SetVolume(percent);
	}
	void SoundManager::SetToGroup(const enums::AudioGroup& group, AudioClip* clip)
	{
		if (clip->GetGroup() != enums::AudioGroup::None)
		{
			auto range = groups.equal_range(clip->GetGroup());
			for (auto iter = range.first; iter != range.second; ++iter)
				if (iter->second == clip)
				{
					groups.erase(iter);
					break;
				}
		}

		groups.insert(std::make_pair(group, clip));
	}
	void SoundManager::Release()
	{
		system->release();
		system = nullptr;
	}
}
