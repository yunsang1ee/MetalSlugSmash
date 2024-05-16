#include "ysEnemyScript.h"
#include <ysTransform.h>
#include <ysGameObject.h>
#include <ysObject.h>
#include <ysTimer.h>
#include <ysRenderer.h>
#include <YSapplication.h>

extern ys::Application app;

ys::EnemyScript::EnemyScript()
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
	auto nextPosition = pos + Vector2::Left * Timer::getDeltaTime() * 600;
	auto cameraPosition = ys::renderer::mainCamera->CalculatPosition(nextPosition);

	if(cameraPosition.x >= 0.0f)
		tr->SetPosition(nextPosition);
	else
		tr->SetPosition(Vector2::Right * app.getScreenf());
}

void ys::EnemyScript::LateUpdate()
{
}

void ys::EnemyScript::Render(HDC hDC)
{
}