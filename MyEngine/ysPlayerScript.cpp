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
#include <ysAnimator.h>
#include <random>

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
		auto an = GetOwner()->GetComponent<Animator>();
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
		{//마우스가 아니라 키보드 상태에 따라 공격방향 정하면 되겠네 $$박경준
			Vector2 position = tr->GetPosition();
			Vector2 mousePosition =
				app.getmousePosition(); //+ Vector2(position.x - app.getScreen().x / 2, position.y - app.getScreen().y / 2);
			position = { position.x + 40, position.y - 40 };
			
			std::random_device rd;
			std::mt19937 engine(rd());
			std::uniform_real_distribution<> urd(-1.0, 1.0);
			auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
				, Vector2(position.x, position.y) + Vector2::One * 10.0f * urd(engine));
			
			if (renderer::mainCamera)
				position = renderer::mainCamera->CalculatPosition(position);

			Vector2 dest = (mousePosition - position).nomalize();
			float degree = acosf(Vector2::Dot(Vector2::Right, dest));
			if (Vector2::Cross(Vector2::Right, dest) < 0)
				degree = 2 * math::kPi - degree;
			auto bulletTr = bullet->GetComponent<Transform>();
			bulletTr->SetRotation(degree);
			bulletTr->SetScale(Vector2::One * 1.5f);

			auto sr = bullet->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"총알png"));

			bullet->AddComponent<BulletScript>();
			bullet->AddComponent<BoxCollider2D>();
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