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
#include<ysAnimator.h>
#include<ysAnimation.h>
#include"PlayerLowerBodyScript.h"

extern ys::Application app;

namespace ys
{
	PlayerScript::PlayerScript() :  coolTime(0), count(0)
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


		switch (state)
		{
		case PlayerScript::PlayerState::Idle:
			idle();
			break;
		case PlayerScript::PlayerState::Move:
			move();
			break;
		case PlayerState::Attack:
			attack();
			break;
		case PlayerState::Sit:
			sit();
			break;
		case PlayerState::Lookup:
			lookup();
			break;
		default:
			break;
		}
		

		auto tr = GetOwner()->GetComponent<Transform>();
		auto an = GetOwner()->GetComponent<Animator>();

		tr->SetPosition({ PlayerLowerBody->GetComponent<Transform>()->GetPosition().x, PlayerLowerBody->GetComponent<Transform>()->GetPosition().y-20 });
		
		
	}
	void PlayerScript::idle()
	{
		auto an = GetOwner()->GetComponent<Animator>();
		auto tr = GetOwner()->GetComponent<Transform>();
		
		if (InputManager::getKey(VK_LEFT))
		{
			state = PlayerState::Move;
			an->PlayAnimation(L"플레이어좌이동상체");
			tr->SetRotation(kPi);
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			state = PlayerState::Move;
			an->PlayAnimation(L"플레이어우이동상체");
			tr->SetRotation(kPi);
		}
		if (InputManager::getKeyDown(VK_SPACE))
		{
			state = PlayerState::Attack;
		}
	}
	void PlayerScript::move()
	{
		auto an = GetOwner()->GetComponent<Animator>();
		auto tr = GetOwner()->GetComponent<Transform>();
		if (InputManager::getKey(VK_LEFT))
		{
			state = PlayerState::Move;
			if (an->GetActive()->getName()!=L"플레이어좌이동상체")
			{
				an->PlayAnimation(L"플레이어좌이동상체");
			}
			
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			state = PlayerState::Move;
			if (an->GetActive()->getName() != L"플레이어우이동상체")
			{
				an->PlayAnimation(L"플레이어우이동상체");
			}

		}
		if (InputManager::getKeyDown(VK_SPACE))
		{
			state = PlayerState::Attack;
		}
		if (InputManager::getKeyDown(VK_UP))
		{
			state = PlayerState::Lookup;
		}
		if (InputManager::getKeyDown(VK_DOWN))
		{
			state = PlayerState::Sit;
			//다운일때는 애니메이션끄기
			//총 쏘는 위치 변경
			//콜리전 영역 축소
		}
		
		if (!InputManager::getKey(VK_LEFT)&&!InputManager::getKey(VK_RIGHT))
		{
			an->PlayAnimation(L"플레이어가만기본");
			state = PlayerState::Idle;
		}
	}
	void PlayerScript::sit()
	{
		if (InputManager::getKeyUp(VK_DOWN))
		{
			state = PlayerState::Idle;
		}
		if (InputManager::getKeyDown(VK_OEM_COMMA))
		{
			state = PlayerState::Slide;
		}
		if (InputManager::getKey(VK_SPACE))
		{
			//슬라이딩하면서 총쏘기
		}
		
	}
	void PlayerScript::slide()
	{
		//애니메이션 끄기
	}
	void PlayerScript::attack()
	{
		if (!coolTime)
		{
			ShootBullet();
			state = PlayerState::Idle;
		}
		
		
	}
	void PlayerScript::lookup()
	{
		if (InputManager::getKeyUp(VK_UP))
		{
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
	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		
	}
	void PlayerScript::OnCollisionStay(Collider* other)
	{
		
	}
	void PlayerScript::OnCollisionExit(Collider* other)
	{

	}
}