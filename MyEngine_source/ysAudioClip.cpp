#include "ysAudioClip.h"
#include <YSapplication.h>
#include <ysSoundManager.h>

extern ys::Application app;
namespace ys
{
	AudioClip::AudioClip() : Resource(enums::ResourceType::AudioClip)
		, sound(nullptr), channel(nullptr)
		, minDistance(1.0f), maxDistance(app.getScreenf().x / 2.0f)
		, loop(false), group(enums::AudioGroup::None)
	{
	}
	AudioClip::~AudioClip()
	{
		sound->release();
		sound = nullptr;
	}
	HRESULT AudioClip::Load(const std::wstring& path)
	{
		std::string sPath{ path.begin(), path.end() };
		if (!SoundManager::CreateSound(sPath, &sound))
			return S_FALSE;

		sound->set3DMinMaxDistance(minDistance, maxDistance);

		return S_OK;
	}
	void AudioClip::Play()
	{
		if (loop)
			sound->setMode(FMOD_LOOP_NORMAL);
		else
			sound->setMode(FMOD_LOOP_OFF);

		SoundManager::SoundPlay(sound, &channel);
	}
	void AudioClip::Stop()
	{
		channel->stop();
	}
	void AudioClip::SetAttributes(const math::Vector2& pos)
	{
		auto nomalizePosition = pos / app.getScreenf();
		FMOD_VECTOR fmodPos(nomalizePosition.x, nomalizePosition.y, 0.0f);
		FMOD_VECTOR fmodVel(0.0f, 0.0f, 0.0f);

		channel->set3DAttributes(&fmodPos, &fmodVel);
	}
	void AudioClip::SetGroup(const enums::AudioGroup& group)
	{
		SoundManager::SetToGroup(group, this);
	}
}