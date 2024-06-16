#include "ysAudioSource.h"
#include "ysGameObject.h"
#include "ysTransform.h"
#include <ysSoundManager.h>

namespace ys
{
	AudioSource::AudioSource() : Component(enums::ComponentType::AudioSource)
	{
	}
	AudioSource::~AudioSource()
	{
	}
	void AudioSource::Init()
	{
	}
	void AudioSource::Update()
	{
	}
	void AudioSource::LateUpdate()
	{
		if (audioClip)
			audioClip->SetAttributes(GetOwner()->GetComponent<Transform>()->GetPosition());
		SoundManager::SetListenerAttributes(GetOwner()->GetComponent<Transform>()->GetPosition());
	}
	void AudioSource::Render(HDC hDC)
	{
	}
	void AudioSource::Play()
	{
		audioClip->Play();
	}
	void AudioSource::Stop()
	{
		audioClip->Stop();
	}
	void AudioSource::SetLoop(const bool& loop)
	{
		audioClip->SetLoop(loop);
	}
}