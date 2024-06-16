#pragma once
#include <ysComponent.h>
#include <ysAudioClip.h>

namespace ys
{
	class AudioSource : public Component
	{
	public:
		AudioSource();
		~AudioSource();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		void Play();
		void Stop();
		void SetLoop(const bool& loop);

		void SetClip(AudioClip* clip) { audioClip = clip; }
		AudioClip* GetClip() 
		{ 
			return audioClip;
		}

	private:
		AudioClip* audioClip;
	};
}

