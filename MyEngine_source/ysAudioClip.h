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
		enums::AudioGroup GetGroup() const { return group; }

		void SetVolume(const float& percent)
		{
			channel->setVolume(percent / 100.0f);
		}

	private:
		FMOD::Sound* sound;
		FMOD::Channel* channel;

		enums::AudioGroup group;
		float minDistance;
		float maxDistance;
		bool loop;
	};
}

