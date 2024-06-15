#pragma once
#include "CommonInclude.h"
#include <ysMath.h>

namespace ys
{
	class SoundManager
	{
	public:
		static void Init();
		static bool CreateSound(const std::string& path, FMOD::Sound** sound);
		static void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);
		static void SetListenerAttributes(const math::Vector2& pos);
		static void SetVolume(const float& percent, const enums::AudioGroup& group);
		static void SetToGroup(const enums::AudioGroup& group, class AudioClip* clip);

		static void Release();

	private:
		static std::unordered_multimap<enums::AudioGroup, class AudioClip*> groups;
		static FMOD::Studio::System* system;
		static FMOD::System* coreSystem;
	};
};