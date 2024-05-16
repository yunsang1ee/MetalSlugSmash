#include "ysEnemyScript.h"
#include <ysTransform.h>
#include <ysGameObject.h>
#include <ysObject.h>
#include <ysTimer.h>

ys::EnemyScript::EnemyScript() : deathTime(6.0f), time(0.0f)
{
}

ys::EnemyScript::~EnemyScript()
{
}

void ys::EnemyScript::Init()
{
}

void ys::EnemyScript::Update()
{
	auto tr = GetOwner()->GetComponent<Transform>();
	auto pos = tr->GetPosition();
	tr->SetPosition(pos + Vector2(Timer::getDeltaTime() * 200, 0));
	time += Timer::getDeltaTime();
	if (time >= deathTime)
		object::Destroy(GetOwner());
}

void ys::EnemyScript::LateUpdate()
{
}

void ys::EnemyScript::Render(HDC hDC)
{
}