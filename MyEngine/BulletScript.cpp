#include "BulletScript.h"
#include <ysTransform.h>
#include <ysGameObject.h>
#include <ysObject.h>
#include <ysTimer.h>
#include <ysRenderer.h>
#include "ysPlayScene.h"

ys::BulletScript::BulletScript() : deathTime(6.0f), time(0.0f), damage(10)
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
	tr->SetPosition(pos + Vector2::Rotate(Vector2::Right, tr->GetRotation()) * Timer::getDeltaTime() * 1200);
	time += Timer::getDeltaTime();
	if (time >= deathTime)
	{
		object::Destroy(GetOwner());
	}
}

void ys::BulletScript::LateUpdate()
{
}

void ys::BulletScript::Render(HDC hDC)
{
}

void ys::BulletScript::OnCollisionEnter(Collider* other)
{
}

void ys::BulletScript::OnCollisionStay(Collider* other)
{
}

void ys::BulletScript::OnCollisionExit(Collider* other)
{
}
