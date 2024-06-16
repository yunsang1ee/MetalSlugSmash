#pragma once
#include "ysResource.h"

namespace ys
{
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		~AudioClip();
		virtual HRESULT Load(const std::wstring& path) override;

		void Play();
		void Stop();
		void SetAttributes(const math::Vector2& pos);
		void SetLoop(const bool& loop) { this->loop = loop; }
		void SetGroup(const enums::AudioGroup& group);
		void SetVolume(const float& percent);
		enums::AudioGroup GetGroup() const { return group; }


	private:
		FMOD::Sound* sound;
		FMOD::Channel* channel;
		float volume;

		enums::AudioGroup group;
		float minDistance;
		float maxDistance;
		bool loop;
	};
}

