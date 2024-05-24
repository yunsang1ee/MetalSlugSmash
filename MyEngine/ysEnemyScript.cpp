#include "ysEnemyScript.h"
#include <ysTransform.h>
#include <ysGameObject.h>
#include <ysObject.h>
#include <ysTimer.h>
#include <ysRenderer.h>
#include <YSapplication.h>
#include <ysSpriteRenderer.h>
#include <ysResources.h>

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
	
	timer += Timer::getDeltaTime();
	if (timer >= 0.1f)
	{
		switch (animation)
		{
		case 0:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게1"));
			animation = 1;
			break;
		case 1:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게2"));
			animation = 2;
			break;
		case 2:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게3"));
			animation = 3;
			break;
		case 3:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게4"));
			animation = 4;
			break;
		case 4:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게5"));
			animation = 5;
			break;
		case 5:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게6"));
			animation = 6;
			break;
		case 6:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게7"));
			animation = 7;
			break;
		case 7:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게8"));
			animation = 8;
			break;
		case 8:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게9"));
			animation = 9;
			break;
		case 9:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게10"));
			animation = 10;
			break;
		case 10:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게11"));
			animation = 11;
			break;
		case 11:
			GetOwner()->GetComponent<SpriteRenderer>()->SetTexture(Resources::Find<graphics::Texture>(L"게12"));
			animation = 0;
			break;
		default:
			break;
		}


		timer = 0;
	}
}

void ys::EnemyScript::LateUpdate()
{
}

void ys::EnemyScript::Render(HDC hDC)
{
}