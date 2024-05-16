#include "BulletScript.h"
#include <ysTransform.h>
#include <ysGameObject.h>
#include <ysObject.h>
#include <ysTimer.h>

ys::BulletScript::BulletScript() : deathTime(6.0f), time(0.0f)
{
}

ys::BulletScript::~BulletScript()
{
}

void ys::BulletScript::Init()
{
}

void ys::BulletScript::Update()
{
	auto tr = GetOwner()->GetComponent<Transform>();
	auto pos = tr->GetPosition();
	tr->SetPosition(pos + tr->GetRotation() * Timer::getDeltaTime() * 600);
	time += Timer::getDeltaTime();
	if (time >= deathTime)
		object::Destroy(GetOwner());
}

void ys::BulletScript::LateUpdate()
{
}

void ys::BulletScript::Render(HDC hDC)
{
}