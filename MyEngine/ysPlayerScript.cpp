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
#include <ysRigidBody.h>
#include<ysCircleCollider2D.h>
#include <ysCollisionManager.h>
#include "STAGE1.h"
#include<random>
#include"ysAnimator.h"

extern ys::Application app;

namespace ys
{
	PlayerScript::PlayerScript() : speed(300), coolTime(0), count(0)
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

		switch (state)
		{
		case ys::PlayerScript::PlayerState::Idle:
			idle();
			break;
		case ys::PlayerScript::PlayerState::Move:
			move();
			break;
		default:
			break;
		}

		
		
		auto tr = GetOwner()->GetComponent<Transform>();
		auto an = GetOwner()->GetComponent<Animator>();
	

		if ((InputManager::getKey(VK_SPACE) || count != 0) && !coolTime&&isTopBody)
		{
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
			auto cc = bullet->AddComponent<CircleCollider2D>();
			cc->SetSize(Vector2(0.2f, 0.2f));
			cc->SetOffset(Vector2(0.5f, 0));
			count++;
			coolTime = 0.05f;//총쏘는 애니메이션 duration동안
			if (count == 5) count = 0;//헤비머신건의 경우 한번에 5발씩 쏘니까 이런식으로 넣어봄 ㅇㅇ
		}
			
		
		if (goingDown)
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y + Timer::getDeltaTime() * speed });
		}
		if (time>1)
		{
			goingDown = true;
			time = 0;
		}
	}
	void PlayerScript::idle()
	{
		auto an = GetOwner()->GetComponent<Animator>();
		if (InputManager::getKey(VK_LEFT))
		{
			state = PlayerState::Move;
			an->PlayAnimation(L"플레이어좌이동상체");
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			state = PlayerState::Move;
			an->PlayAnimation(L"플레이어우이동상체");
		}
		if (InputManager::getKey(VK_UP))
		{
			state = PlayerState::Move;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			state = PlayerState::Move;
		}
	}
	void PlayerScript::move()
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto an = GetOwner()->GetComponent<Animator>();
		if (InputManager::getKey(VK_LEFT))
		{
			direction = BulletDirection::Left;
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x - Timer::getDeltaTime() * speed, position.y });
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			direction = BulletDirection::Right;
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x + Timer::getDeltaTime() * speed, position.y });
		}
		if (InputManager::getKey(VK_UP))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y - Timer::getDeltaTime() * speed });
			direction = BulletDirection::Up;
		}
		if (InputManager::getKey(VK_DOWN))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x, position.y + Timer::getDeltaTime() * speed });
			direction = BulletDirection::Down;

		}
		if (InputManager::getKeyUp(VK_UP) || InputManager::getKeyUp(VK_RIGHT) || InputManager::getKeyUp(VK_LEFT) || InputManager::getKeyUp(VK_DOWN))
		{
			an->PlayAnimation(L"플레이어가만기본", true);
			state = PlayerState::Idle;
		}
		
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hDC)
	{
	}
	void PlayerScript::ShootBullet()
	{

		auto tr = GetOwner()->GetComponent<Transform>();
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


	}
	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		
		//타입캐스트로 게임오브젝트에서 레이어로 할수가없음 상속이 안되었는지
		
		//콜리전이 하나의 오브젝트에 여러개 필요함 발판 콜리젼
		//충돌 콜리젼
		//점프할때 충돌 off->무적됨
		//충돌 off안하면 몸통 콜리젼때문에 플랫폼통과 못하거나 플랫폼에 낌
		//발판 콜리젼을 이요해서 이동과 충돌 콜리젼을 따로 처리해야함
		if (other->getName()==L"Block")//레이어 타입을 알수 없음
		{
			auto otherPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();
			auto thisPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			thisPos = otherPos-thisPos;
		}
		if (other->getName() == L"BackGround") {
			goingDown = false;
		}
		
		
		
	}
	void PlayerScript::OnCollisionStay(Collider* other)
	{
		
		if (other->getName() == L"BackGround") {
			goingDown = false;
		}
	}
	void PlayerScript::OnCollisionExit(Collider* other)
	{
		
	}

}