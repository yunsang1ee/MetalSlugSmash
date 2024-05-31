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
#include <ysRigidBody.h>

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

		if ((InputManager::getKey((UINT)Key::B) || count != 0) && !coolTime)
		{//마우스가 아니라 키보드 상태에 따라 공격방향 정하면 되겠네 $$박경준
			ShootBullet();
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
		
		auto bulletTr = bullet->GetComponent<Transform>();
		bulletTr->SetRotation(tr->GetRotation());
		bulletTr->SetScale(Vector2::One * 1.5f);

		auto sr = bullet->AddComponent<SpriteRenderer>();//Animation
		sr->SetTexture(Resources::Find<graphics::Texture>(L"총알png"));

		bullet->AddComponent<BulletScript>();
		bullet->AddComponent<BoxCollider2D>();
		count++;
		coolTime = 0.05f;//총쏘는 애니메이션 duration동안
		if (count == 5) count = 0;//헤비머신건의 경우 한번에 5발씩 쏘니까 이런식으로 넣어봄 ㅇㅇ
	}
	void PlayerScript::OnCollisionEnter(Collider* other)
	{
	}
	void PlayerScript::OnCollisionStay(Collider* other)
	{
	}
	void PlayerScript::OnCollisionExit(Collider* other)
	{
	}
	void PlayerScript::idle()
	{
		auto an = GetOwner()->GetComponent<Animator>();
		if (InputManager::getKey(VK_LEFT))
		{
			state = PlayerState::Move;
			if (isTopBody)
				an->PlayAnimation(L"플레이어좌이동상체");
			else
				an->PlayAnimation(L"플레이어좌이동하체");

		}
		if (InputManager::getKey(VK_RIGHT))
		{
			state = PlayerState::Move;
			if (isTopBody)
				an->PlayAnimation(L"플레이어우이동상체");
			else
				an->PlayAnimation(L"플레이어우이동하체");
		}
		if (InputManager::getKey(VK_UP))
		{
			state = PlayerState::Move;
		}
		if (InputManager::getKey(VK_OEM_COMMA))
		{
			auto rb = GetOwner()->GetComponent<RigidBody>();
			if(rb->IsGround())
			{
				auto velocity = rb->GetVelocity();
				velocity.y = -800.0f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);
			}
		}
		if (InputManager::getKey(VK_DOWN))
		{
			state = PlayerState::Move;
		}
	}

	void PlayerScript::move()
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto rb = GetOwner()->GetComponent<RigidBody>();
		if (InputManager::getKey(VK_LEFT))
		{
			tr->SetRotation(kPi);
			rb->AddForce(Vector2::Left * speed);
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			tr->SetRotation(0.0f);
			rb->AddForce(Vector2::Right * speed);
		}
		if (InputManager::getKey(VK_UP))
		{
			auto curRotation = tr->GetRotation();
			if (curRotation > kPi / 2.0f)
				tr->SetRotation(curRotation - kPi / 6.0f);
			else if (curRotation < kPi / 2.0f)
				tr->SetRotation(curRotation + kPi / 6.0f);
		}
		if (InputManager::getKey(VK_OEM_COMMA) && rb->IsGround())
		{
			auto velocity = rb->GetVelocity();
			velocity.y = -800.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
		}
		if (InputManager::getKey(VK_DOWN))
		{
			rb->AddForce(Vector2::Down * speed);
		}

		if (InputManager::getKeyUp(VK_LEFT)
			|| InputManager::getKeyUp(VK_RIGHT)
			|| InputManager::getKeyUp(VK_UP)
			|| InputManager::getKeyUp(VK_DOWN))
		{
			auto an = GetOwner()->GetComponent<Animator>();
			if (isTopBody)
				an->PlayAnimation(L"플레이어가만기본");
			else
				an->PlayAnimation(L"플레이어가만하체");

			if (!InputManager::getKeyUp(VK_UP))
			{
				auto rb = GetOwner()->GetComponent<RigidBody>();
				rb->SetVelocity(Vector2(0.0f, rb->GetVelocity().y));
			}

			state = PlayerState::Idle;
		}
	}
}