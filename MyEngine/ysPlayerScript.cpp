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
#include<ysCircleCollider2D.h>
#include <ysCollisionManager.h>
#include"ysBoxCollider2D.h"
#include "STAGE1.h"
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
		auto thisOwner = this;
		auto thisScene = dynamic_cast<Scene*>(thisOwner);
		
		time += Timer::getDeltaTime();
		
		
		static int animation = 0;
		
		auto tr = GetOwner()->GetComponent<Transform>();
		auto sr = GetOwner()->GetComponent<SpriteRenderer>();
		if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT))
		{
			switch (animation)
			{
			case 0:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동1"));
				animation++;
				break;
			case 1:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동2"));
				animation++;
				break;
			case 2:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동3"));
				animation++;
				break;
			case 3:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동4"));
				animation++;
				break;
			case 4:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동5"));
				animation++;
				break;
			case 5:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동6"));
				animation = 0;
				break;
			default:
				break;
			}
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x - Timer::getDeltaTime() * speed, position.y });
		}
		if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT))
		{
			switch (animation)
			{
			case 0:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동1"));
				animation++;
				break;
			case 1:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동2"));
				animation++;
				break;
			case 2:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동3"));
				animation++;
				break;
			case 3:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동4"));
				animation++;
				break;
			case 4:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동5"));
				animation++;
				break;
			case 5:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동6"));
				animation = 0;
				break;
			default:
				break;
			}
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x + Timer::getDeltaTime() * speed, position.y });
		}
		if (InputManager::getKey((BYTE)ys::Key::W) || InputManager::getKey(VK_UP))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y - Timer::getDeltaTime() * speed });
			
			if (goingDown) {
				goingDown = false;
			}
			
		}
		if (InputManager::getKey((BYTE)ys::Key::S) || InputManager::getKey(VK_DOWN))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y + Timer::getDeltaTime() * speed });
		}

		if ((InputManager::getKey(VK_LBUTTON) || count != 0) && !coolTime)
		{//마우스가 아니라 키보드 상태에 따라 공격방향 정하면 되겠네 $$박경준
			auto position = tr->GetPosition();
			auto mousePosition = 
				app.getmousePosition() + Vector2(position.x - app.getScreen().x / 2, position.y - app.getScreen().y / 2);
			position = { position.x + 100, position.y + 60 };
			auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
				, { position.x, position.y});

			auto dest = mousePosition - position;
			bullet->GetComponent<Transform>()->SetRotation(dest.nomalize());

			auto sr = bullet->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"총알"));

			bullet->AddComponent<BulletScript>();
			auto cc = bullet->AddComponent<CircleCollider2D>();
			cc->SetSize(Vector2(0.2f, 0.2f));
			cc->SetOffset(Vector2(0.5f, 0));
			count++;
			coolTime = 0.05f;//총쏘는 애니메이션 duration동안
			if (count == 5) count = 0;//헤비머신건의 경우 한번에 5발씩 쏘니까 이런식으로 넣어봄 ㅇㅇ
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
		if (goingDown)
		{
			
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y + Timer::getDeltaTime() * speed });
		}
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hDC)
	{
	}
	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		
		if (CollisionManager::Intersect(GetOwner()->GetComponent<CircleCollider2D>(), other)&&other->getName()==L"Block")
		{
			auto otherPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();
			auto thisPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			thisPos = Vector2{ thisPos.x - (otherPos.x - thisPos.x),thisPos.y - (otherPos.y - thisPos.y) };
		}
		if (CollisionManager::Intersect(GetOwner()->GetComponent<CircleCollider2D>(), other) && other->getName() == L"BackGround") {
			goingDown = false;
		}
		else {
			if (time > 1)
			{
				goingDown = true;
				time = 0;
			}
		}
		
		
	}
	void PlayerScript::OnCollisionStay(Collider* other)
	{
		if (CollisionManager::Intersect(GetOwner()->GetComponent<CircleCollider2D>(), other) && other->getName() == L"BackGround") {
			goingDown = false;
		}
		else {
			if (time > 10)
			{
				goingDown = true;
				time = 0;
			}
		}
		
	}
	void PlayerScript::OnCollisionExit(Collider* other)
	{
		
	}
}