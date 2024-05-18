#include "ysPlayerScript.h"
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

extern ys::Application app;

namespace ys
{
	PlayerScript::PlayerScript() : prevPosition({ 0, 0 }), speed(300), coolTime(0), count(0)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Init()
	{
		
	}
	void PlayerScript::Update()
	{
		if (coolTime >= 0)
			coolTime -= Timer::getDeltaTime();
		else
			coolTime = 0.0f;

		auto tr = GetOwner()->GetComponent<Transform>();
		if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x - Timer::getDeltaTime() * speed, position.y });
		}
		if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x + Timer::getDeltaTime() * speed, position.y });
		}
		if (InputManager::getKey((BYTE)ys::Key::W) || InputManager::getKey(VK_UP))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y - Timer::getDeltaTime() * speed });
		}
		if (InputManager::getKey((BYTE)ys::Key::S) || InputManager::getKey(VK_DOWN))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y + Timer::getDeltaTime() * speed });
		}

		if ((InputManager::getKey(VK_LBUTTON) || count != 0) && !coolTime)
		{//���콺�� �ƴ϶� Ű���� ���¿� ���� ���ݹ��� ���ϸ� �ǰڳ� $$�ڰ���
			auto position = tr->GetPosition();
			auto mousePosition = 
				app.getmousePosition() + Vector2(position.x - app.getScreen().x / 2, position.y - app.getScreen().y / 2);
			position = { position.x + 100, position.y + 60 };
			auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
				, { position.x, position.y});

			auto dest = mousePosition - position;
			bullet->GetComponent<Transform>()->SetRotation(dest.nomalize());

			auto sr = bullet->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�Ѿ�"));

			bullet->AddComponent<BulletScript>();
			bullet->AddComponent<BoxCollider2D>();
			count++;
			coolTime = 0.05f;//�ѽ�� �ִϸ��̼� duration����
			if (count == 5) count = 0;//���ӽŰ��� ��� �ѹ��� 5�߾� ��ϱ� �̷������� �־ ����
		}
			
		if (InputManager::getKey((BYTE)ys::Key::U) && !coolTime)
		{
			speed += 10.0f;
			coolTime = 0.1f;
		}
		if (InputManager::getKey((BYTE)ys::Key::I) && !coolTime)
		{
			speed -= 10.0f;
			coolTime = 0.1f;
		}
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hDC)
	{
	}
}