#include "ysAudioListener.h"
#include "ysGameObject.h"
#include "ysTransform.h"
#include <ysSoundManager.h>
#include <ysRenderer.h>

namespace ys
{
	AudioListener::AudioListener() : Component(enums::ComponentType::AudioListener)
	{
	}
	AudioListener::~AudioListener()
	{
	}
	void AudioListener::Init()
	{
	}
	void AudioListener::Update()
	{
	}
	void AudioListener::LateUpdate()
	{
		SoundManager::SetListenerAttributes(GetOwner()->GetComponent<Transform>()->GetPosition());
	}
	void AudioListener::Render(HDC hDC)
	{
	}
}