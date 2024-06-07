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
	PlayerScript::PlayerScript() : coolTime(0), count(0)
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
		bulletStartPos = tr->GetPosition();
		switch (state)
		{
		case PlayerState::Idle:
			idle();
			break;
		case PlayerState::Move:
			move();
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
		
		auto an = GetOwner()->GetComponent<Animator>();

		tr->SetPosition({ PlayerLowerBody->GetComponent<Transform>()->GetPosition().x, PlayerLowerBody->GetComponent<Transform>()->GetPosition().y-20 });
	}
	void PlayerScript::NextAnimation()
	{
		auto an = GetOwner()->GetComponent<Animator>();
		if (an->GetActive()->getName() == L"플레이어_기본총_우공격_화염" || an->GetActive()->getName() == L"플레이어_기본총_좌공격_화염")
		{
			if (direction == Vector2::Right)
			{
				an->PlayAnimation(L"플레이어_기본총_우공격_달리기", false);
				
			}
			else
			{
				an->PlayAnimation(L"플레이어_기본총_좌공격_달리기", false);
			}
			return;
		}
		if (an->GetActive()->getName() == L"플레이어_기본총_우공격_달리기" || an->GetActive()->getName() == L"플레이어_기본총_좌공격_달리기")
		{
			if (state==PlayerState::Move)
			{
				if (direction==Vector2::Right)
				{
					an->PlayAnimation(L"플레이어우이동상체");
				}
				else {
					an->PlayAnimation(L"플레이어좌이동상체");
				}
				return;
			}
			if (state==PlayerState::Idle)
			{
				an->PlayAnimation(L"플레이어가만기본");
				return;
			}
			
		}
	}
	void PlayerScript::idle()
	{
		auto an = GetOwner()->GetComponent<Animator>();
		auto tr = GetOwner()->GetComponent<Transform>();
		
		if (InputManager::getKey(VK_LEFT))
		{
			state = PlayerState::Move;
			an->PlayAnimation(L"플레이어좌이동상체");
			direction = Vector2::Left;
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			state = PlayerState::Move;
			an->PlayAnimation(L"플레이어우이동상체");
			direction = Vector2::Right;
		}
		if (InputManager::getKeyDown(VK_SPACE))
		{
			if (direction == Vector2::Left)
			{
				an->PlayAnimation(L"플레이어_기본총_우공격_가만", false);
			}
			else {
				an->PlayAnimation(L"플레이어_기본총_좌공격_가만", false);
			}
			ShootBullet();
		}
		if (InputManager::getKeyDown(VK_UP))
		{
			state = PlayerState::Lookup;
		}
		if (InputManager::getKeyDown(VK_DOWN))
		{
			state = PlayerState::Sit;
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
			bulletStartPos = { GetOwner()->GetComponent<Transform>()->GetPosition().x - 40, GetOwner()->GetComponent<Transform>()->GetPosition().y};
			tr->SetRotation(kPi);
			direction = Vector2::Left;
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			state = PlayerState::Move;
			if (an->GetActive()->getName() != L"플레이어우이동상체")
			{
				an->PlayAnimation(L"플레이어우이동상체");
			}
			bulletStartPos = { GetOwner()->GetComponent<Transform>()->GetPosition().x + 40, GetOwner()->GetComponent<Transform>()->GetPosition().y };
			tr->SetRotation(kPi);
			direction = Vector2::Right;
		}
		if (InputManager::getKeyDown(VK_SPACE))
		{
			if (direction==Vector2::Right)
			{
				an->PlayAnimation(L"플레이어_기본총_우공격_달기기", false);
			}
			else {
				an->PlayAnimation(L"플레이어_기본총_좌공격_달기기", false);
			}
			ShootBullet();
		}
		if (InputManager::getKeyDown(VK_UP))
		{
			if (an->GetActive()->getName() != L"플레이어기본총위상체" && direction == Vector2::Right)
			{
				an->PlayAnimation(L"플레이어기본총위상체");
			}
			else if (an->GetActive()->getName() != L"플레이어기본총위상체좌" && direction == Vector2::Left)
			{
				an->PlayAnimation(L"플레이어기본총위상체좌");
			}
			state = PlayerState::Lookup;
		}
		if (InputManager::getKeyDown(VK_DOWN))
		{
			state = PlayerState::Sit;
		}
		
		if (InputManager::getKeyUp(VK_RIGHT))
		{
			if (direction == Vector2::Left)
			{
				an->PlayAnimation(L"플레이어가만기본좌");
			}
			else {
				an->PlayAnimation(L"플레이어가만기본");
			}
			state = PlayerState::Idle;
		}
		if(InputManager::getKeyUp(VK_LEFT))
		{
			an->PlayAnimation(L"플레이어가만기본좌");
			state = PlayerState::Idle;
		}
	}
	void PlayerScript::sit()
	{
		//총쏘는 위치 변경
		auto tr = GetOwner()->GetComponent<Transform>();
		bulletStartPos = { bulletStartPos.x , GetOwner()->GetComponent<Transform>()->GetPosition().y + 20 };
		auto an = GetOwner()->GetComponent<Animator>();
		if (an->GetActive()->getName()!= L"플레이어가만안보임")
		{
			an->PlayAnimation(L"플레이어가만안보임");
		}
		if (InputManager::getKey(VK_DOWN))
		{
			state = PlayerState::Sit;
		}
		if (InputManager::getKeyUp(VK_DOWN))
		{
			if (direction == Vector2::Left)
			{
				an->PlayAnimation(L"플레이어가만기본좌");
			}
			else {
				an->PlayAnimation(L"플레이어가만기본");
			}
			state = PlayerState::Idle;
		}
		if (InputManager::getKey(VK_LEFT))
		{
			direction = Vector2::Left;
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			direction = Vector2::Right;
		}
		if (InputManager::getKeyDown(VK_OEM_COMMA))
		{
			state = PlayerState::Slide;
		}
		if (InputManager::getKeyDown(VK_SPACE))
		{
			ShootBullet();
		}
		
	}
	void PlayerScript::slide()
	{
		//애니메이션 끄기
		auto tr = GetOwner()->GetComponent<Transform>();
		auto an = GetOwner()->GetComponent<Animator>();
		if (an->GetActive()->getName() != L"플레이어안보임") {
			an->PlayAnimation(L"플레이어안보임");
		}

		
	}
	void PlayerScript::attack()
	{
		//보고있는 방향으로 총쏘기
		
	}
	void PlayerScript::lookup()
	{
  		auto an = GetOwner()->GetComponent<Animator>();
		bulletStartPos = { bulletStartPos.x, GetOwner()->GetComponent<Transform>()->GetPosition().y - 40 };
		
		if (InputManager::getKey(VK_UP))
		{
			state = PlayerState::Lookup;
		}
		if (InputManager::getKeyUp(VK_UP))
		{
			if (direction == Vector2::Left)
			{
				an->PlayAnimation(L"플레이어가만기본좌");
			}
			else {
				an->PlayAnimation(L"플레이어가만기본");
			}
			state = PlayerState::Idle;
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			direction = Vector2::Right;
		}
		if (InputManager::getKey(VK_LEFT))
		{
			direction = Vector2::Left;
		}
		if (InputManager::getKeyDown(VK_SPACE))
		{
			direction = Vector2::Up;
			ShootBullet();
		}
		if (InputManager::getKeyDown(VK_DOWN))
		{
			state = PlayerState::Sit;
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
		//Vector2 position = tr->GetPosition();
		Vector2 mousePosition =
			app.getmousePosition(); //+ Vector2(position.x - app.getScreen().x / 2, position.y - app.getScreen().y / 2);
		//position = { position.x + 40, position.y - 40 };

		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_real_distribution<> urd(-1.0, 1.0);
		auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
			, Vector2(bulletStartPos.x, bulletStartPos.y) + Vector2::One * 10.0f * urd(engine));

		if (renderer::mainCamera)
			bulletStartPos = renderer::mainCamera->CalculatPosition(bulletStartPos);

		//Vector2 dest = (mousePosition - bulletStartPos).nomalize();
		Vector2 dest = direction;
		float degree = acosf(Vector2::Dot(Vector2::Right, dest));
		if (Vector2::Cross(Vector2::Right, dest) < 0)
			degree = 2 * math::kPi - degree;
		auto bulletTr = bullet->GetComponent<Transform>();
		bulletTr->SetRotation(degree);
		bulletTr->SetScale(Vector2::One * 1.5f);

		auto sr = bullet->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"총알png"));

		bullet->AddComponent<BulletScript>();
		bullet->AddComponent<CircleCollider2D>()->SetSize(Vector2(0.02f,0.02f));//setsize가 작동안함
		bullet->AddComponent<CircleCollider2D>()->SetOffset(Vector2(0, 0));
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