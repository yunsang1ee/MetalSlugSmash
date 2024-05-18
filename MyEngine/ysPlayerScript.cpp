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
		auto sr = GetOwner()->GetComponent<SpriteRenderer>();
		if (!(InputManager::getKey((BYTE)ys::Key::W) || InputManager::getKey(VK_UP)))
		{
			if (tr->GetPosition().y < 442)
			{
				tr->SetPosition({ tr->GetPosition().x, tr->GetPosition().y + Timer::getDeltaTime() * 300 });//플레이어가 화면 밖으로 나가지 않게 하기 위한 코드

			}
		}
		
		static int runAnimation = 0;
		if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x - Timer::getDeltaTime() * speed, position.y });
			
			
			//프레임마다 텍스쳐가 바뀌므로 프레임수가 높으면 너무 빠르게 움직이고 낮으면 너무 느리게 움직임
			switch (runAnimation)
			{
			case 0:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동1"));
				runAnimation++;
				break;
			case 1:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동2"));
				runAnimation++;
				break;
			case 2:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동3"));
				runAnimation++;
				break;
			case 3:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동4"));
				runAnimation++;
				break;
			case 4:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동5"));
				runAnimation++;
				break;
			case 5:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동6"));
				runAnimation = 0;
				break;
			default:
				break;
			}
		}
		if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x + Timer::getDeltaTime() * speed, position.y });
			switch (runAnimation)
			{
			case 0:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동1"));
				runAnimation++;
				break;
			case 1:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동2"));
				runAnimation++;
				break;
			case 2:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동3"));
				runAnimation++;
				break;
			case 3:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동4"));
				runAnimation++;
				break;
			case 4:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동5"));
				runAnimation++;
				break;
			case 5:
				sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어이동6"));
				runAnimation = 0;
				break;
			default:
				break;
			}
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

		if ((InputManager::getKey(VK_SPACE) || count != 0) && !coolTime)
		{//마우스가 아니라 키보드 상태에 따라 공격방향 정하면 되겠네 $$박경준
			//지금은 마우스로 공격 방향 정하고 있는건가?
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
			bullet->AddComponent<BoxCollider2D>();
			auto col = bullet->GetComponent<BoxCollider2D>();
			col->SetSize(Vector2(0.7, 0.2));
			
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
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hDC)
	{
	}
}