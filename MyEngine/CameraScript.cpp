#include "CameraScript.h"
#include <ysCamera.h>
#include <ysTransform.h>
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
	auto cmr = GetOwner()->GetComponent<Camera>();
	auto targetTr = target->GetComponent<Transform>();
	
	if (targetTr->GetPosition().x<0)
	{

	}
	else {
		cmr->SetTarget(Backgrounf)
	}
}

void ys::CameraScript::LateUpdate()
{
}

void ys::CameraScript::Render(HDC hDC)
{
}
