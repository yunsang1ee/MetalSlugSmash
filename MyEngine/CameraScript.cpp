#include "CameraScript.h"
#include <ysCamera.h>
#include <ysTransform.h>
#include <ysAudioSource.h>

namespace ys
{
	ys::CameraScript::CameraScript()
	{
	}

	ys::CameraScript::~CameraScript()
	{
	}

	void ys::CameraScript::Init()
	{
	}

	void ys::CameraScript::Update()
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		if (target)
			tr->SetPosition(target->GetComponent<Transform>()->GetPosition());
	}

	void ys::CameraScript::LateUpdate()
	{
	}

	void ys::CameraScript::Render(HDC hDC)
	{
	}
}

