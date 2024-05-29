#include "pracPlayerScript.h"
#include "ysGameObject.h"
#include "ysTimer.h"
#include "ysInputManager.h"
#include <ysTransform.h>
#include <ysObject.h>
#include "ysPlayer.h"
#include "YSapplication.h"
#include <ysSpriteRenderer.h>
#include <ysResources.h>
#include "ysEnemyScript.h"
#include "BulletScript.h"
#include <ysBoxCollider2D.h>
#include <ysRenderer.h>
#include<ysCircleCollider2D.h>
#include <ysCollisionManager.h>
#include"ysBoxCollider2D.h"
#include "5-5.h"
#include "ysTexture.h"
extern ys::Application app;
pracPlayerScript::pracPlayerScript()
{
}

pracPlayerScript::~pracPlayerScript()
{
}

void pracPlayerScript::Init()
{
}

void pracPlayerScript::Update()
{
	if (coolTime >= 0)
		coolTime -= Timer::getDeltaTime();
	else
		coolTime = 0.0f;
	auto thisOwner = this;
	auto thisScene = dynamic_cast<Scene*>(thisOwner);

	time += Timer::getDeltaTime();


	static int animation = 0;

	auto tr = GetOwner()->GetComponent<Transform>();
	auto sr = GetOwner()->GetComponent<SpriteRenderer>();
	if (InputManager::getKey(VK_LEFT))
	{
		auto position = tr->GetPosition();
		tr->SetPosition({ position.x - Timer::getDeltaTime() * speed, position.y });
		sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��(��)"));
		bulletDirection = pracPlayerScript::left;
	}
	if (InputManager::getKey(VK_RIGHT))
	{
		auto position = tr->GetPosition();
		tr->SetPosition({ position.x + Timer::getDeltaTime() * speed, position.y });
		bulletDirection = pracPlayerScript::right;
	}
	if (InputManager::getKey(VK_UP))
	{
		auto position = tr->GetPosition();
		tr->SetPosition({ position.x, position.y - Timer::getDeltaTime() * speed });
		bulletDirection = pracPlayerScript::up;
	}
	if (InputManager::getKey(VK_DOWN))
	{
		auto position = tr->GetPosition();
		tr->SetPosition({ position.x, position.y + Timer::getDeltaTime() * speed });
		bulletDirection = pracPlayerScript::down;
	}
	if ((InputManager::getKey(VK_SPACE)) && !coolTime)
	{//���콺�� �ƴ϶� Ű���� ���¿� ���� ���ݹ��� ���ϸ� �ǰڳ� $$�ڰ���
		auto position = tr->GetPosition();
		
		position = { position.x + 100, position.y + 60 };
		auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
			, { position.x, position.y });
		auto sr = bullet->AddComponent<SpriteRenderer>();
		
		Vector2 dest;
		switch (bulletDirection)
		{
		case pracPlayerScript::left:
			dest = position.Left;
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ˿���"));
			break;
		case pracPlayerScript::right:
			dest = position.Right;
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ�"));
			break;
		case pracPlayerScript::up:
			dest = position.Up;
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ���"));
			
			break;
		case pracPlayerScript::down:
			dest = position.Down;
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ˾Ʒ�"));
			break;
		default:
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ�"));
			break;
		}
		
		
		bullet->GetComponent<Transform>()->SetRotation(dest.nomalize());

		

		bullet->AddComponent<BulletScript>();
		auto cc = bullet->AddComponent<CircleCollider2D>();
		cc->SetSize(Vector2(0.2f, 0.2f));
		cc->SetOffset(Vector2(0.5f, 0));
		//count++;
		coolTime = 0.05f;//�ѽ�� �ִϸ��̼� duration����
		//if (count == 5) count = 0;//���ӽŰ��� ��� �ѹ��� 5�߾� ��ϱ� �̷������� �־ ����
	}

}

void pracPlayerScript::LateUpdate()
{
}

void pracPlayerScript::Render(HDC hDC)
{
}

void pracPlayerScript::OnCollisionEnter(Collider* other)
{
}

void pracPlayerScript::OnCollisionStay(Collider* other)
{
}

void pracPlayerScript::OnCollisionExit(Collider* other)
{
}
