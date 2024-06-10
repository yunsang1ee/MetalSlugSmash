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
	PlayerScript::PlayerScript() : count(0)
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
		if (!ownerAnimator)
			ownerAnimator = GetOwner()->GetComponent<Animator>();

		if (count != 0 && ownerAnimator->GetActive()->IsComplete())
			ShootBullet();

		auto tr = GetOwner()->GetComponent<Transform>();
		switch (state)
		{
		case PlayerScript::PlayerState::Idle:
			idle();
			break;
		case PlayerScript::PlayerState::IdleJump:
			idle_Jump();
			break;
		case PlayerScript::PlayerState::Move:
			move();
			break;
		case PlayerScript::PlayerState::Grenade:
			grenade();
			break;
		case PlayerScript::PlayerState::Sit:
			sit();
			break;
		case PlayerScript::PlayerState::LookDown:
			lookDown();
			break;
		case PlayerScript::PlayerState::LookDownAttack:
			lookDown_Attack();
			break;
		case PlayerScript::PlayerState::JumpAttack:
			jump_Attack();
			break;
		case PlayerScript::PlayerState::MoveJump:
			move_Jump();
			break;
		case PlayerScript::PlayerState::IdleAttack:
			idle_Attack();
			break;
		case PlayerScript::PlayerState::LookUp:
			lookUp();
			break;
		case PlayerScript::PlayerState::LookUpAttack:
			lookUp_Attack();
			break;
		default:
			break;
		}

		tr->SetPosition({ playerLowerBody->GetComponent<Transform>()->GetPosition().x, playerLowerBody->GetComponent<Transform>()->GetPosition().y-20 });
	}

	void PlayerScript::idle()
	{
		if (InputManager::getKey(VK_OEM_COMMA))
		{
			state = PlayerState::IdleJump;
		}
		if (InputManager::getKey(VK_LEFT))
		{
			direction = kPi;
			GetOwner()->GetComponent<Transform>()->SetRotation(kPi);
			ownerAnimator->PlayAnimation(L"플레이어이동상체좌");
			state = PlayerState::Move;
		}
		if (InputManager::getKey(VK_RIGHT))
		{
			direction = 0.0f;
			GetOwner()->GetComponent<Transform>()->SetRotation(0);
			ownerAnimator->PlayAnimation(L"플레이어이동상체");
			state = PlayerState::Move;
		}
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (direction == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체", false);
			state = PlayerState::IdleAttack;
		}
		if (InputManager::getKey(VK_UP))
		{

			state = PlayerState::LookUp;
		}
		if (InputManager::getKey(VK_DIVIDE))
		{

			state = PlayerState::Grenade;
		}
		if (InputManager::getKey(VK_DOWN))
		{

			state = PlayerState::Sit;
		}
		/*auto an = GetOwner()->GetComponent<Animator>();
		auto tr = GetOwner()->GetComponent<Transform>();
		if (direction == Vector2::Left)
		{
			an->PlayAnimation(L"플레이어가만기본좌");
		}
		else {
			an->PlayAnimation(L"플레이어가만기본");
		}
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
			ShootBullet();
		}
		if (InputManager::getKeyDown(VK_UP))
		{
			state = PlayerState::Lookup;
		}
		if (InputManager::getKeyDown(VK_DOWN))
		{
			state = PlayerState::Sit;
		}*/
	}

	void PlayerScript::idle_Jump()
	{
		if (playerLowerBody->GetComponent<RigidBody>()->IsGround())
		{
			auto rotation = GetOwner()->GetComponent<Transform>()->GetRotation();
			if(rotation == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만기본좌");
			else
				ownerAnimator->PlayAnimation(L"플레이어가만기본");
			state = PlayerState::Idle;
		}
	}

	void PlayerScript::move()
	{
		if (InputManager::getKey(VK_OEM_COMMA))
		{
			//state = PlayerState::MoveJump;
		}
		if (InputManager::getKey(VK_OEM_PERIOD))
		{
			if (direction == kPi)
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체좌", false);
			else
				ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체", false);
			state = PlayerState::IdleAttack;
		}
		if (InputManager::getKey(VK_UP))
		{

			state = PlayerState::LookUp;
		}
		if (InputManager::getKey(VK_DIVIDE))
		{

			state = PlayerState::Grenade;
		}
		if (InputManager::getKey(VK_DOWN))
		{

			state = PlayerState::Sit;
		}

		if (InputManager::getKeyUp(VK_LEFT))
		{
			ownerAnimator->PlayAnimation(L"플레이어가만기본좌", true);
			state = PlayerState::Idle;
		}
		if (InputManager::getKeyUp(VK_RIGHT))
		{
			ownerAnimator->PlayAnimation(L"플레이어가만기본", true);
			state = PlayerState::Idle;
		}
		/*auto an = GetOwner()->GetComponent<Animator>();
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
		
		if (InputManager::getKeyUp(VK_RIGHT))
		{
			an->PlayAnimation(L"플레이어가만기본");
			state = PlayerState::Idle;
		}
		if(InputManager::getKeyUp(VK_LEFT))
		{
			an->PlayAnimation(L"플레이어가만기본좌");
			state = PlayerState::Idle;
		}*/
	}

	void PlayerScript::grenade()
	{
	}

	void PlayerScript::sit()
	{
		////총쏘는 위치 변경
		//auto tr = GetOwner()->GetComponent<Transform>();
		//bulletStartPos = { bulletStartPos.x , GetOwner()->GetComponent<Transform>()->GetPosition().y + 20 };
		//auto an = GetOwner()->GetComponent<Animator>();
		//if (an->GetActive()->getName()!= L"플레이어가만안보임")
		//{
		//	an->PlayAnimation(L"플레이어가만안보임");
		//}
		//if (InputManager::getKey(VK_DOWN))
		//{
		//	state = PlayerState::Sit;
		//}
		//if (InputManager::getKeyUp(VK_DOWN))
		//{
		//	an->PlayAnimation(L"플레이어가만기본");
		//	state = PlayerState::Idle;
		//}
		//if (InputManager::getKey(VK_LEFT))
		//{
		//	direction = Vector2::Left;
		//}
		//if (InputManager::getKey(VK_RIGHT))
		//{
		//	direction = Vector2::Right;
		//}
		//if (InputManager::getKeyDown(VK_OEM_COMMA))
		//{
		//	state = PlayerState::Slide;
		//}
		//if (InputManager::getKeyDown(VK_SPACE))
		//{
		//	ShootBullet();
		//}
		
	}

	void PlayerScript::lookDown()
	{
	}

	void PlayerScript::lookDown_Attack()
	{
	}

	void PlayerScript::jump_Attack()
	{
	}

	void PlayerScript::move_Jump()
	{
	}
	//void PlayerScript::slide()
	//{
	//	//애니메이션 끄기
	//	/*auto tr = GetOwner()->GetComponent<Transform>();
	//	auto an = GetOwner()->GetComponent<Animator>();
	//	if (an->GetActive()->getName() != L"플레이어안보임") {
	//		an->PlayAnimation(L"플레이어안보임");
	//	}*/
	//
	//	
	//}
	void PlayerScript::idle_Attack()
	{
		//보고있는 방향으로 총쏘기
		if(ownerAnimator->IsComplete())
		{
			if (InputManager::getKey(VK_LEFT))
			{
				direction = kPi;
				GetOwner()->GetComponent<Transform>()->SetRotation(kPi);
			}
			if (InputManager::getKey(VK_RIGHT))
			{
				direction = 0.0f;
				GetOwner()->GetComponent<Transform>()->SetRotation(0.0f);
			}
			if (InputManager::getKey(VK_OEM_PERIOD))
			{
				if (direction == kPi)
					ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체좌", false);
				else
					ownerAnimator->PlayAnimation(L"플레이어가만총쏘는중상체", false);
			}
			else
			{
				ownerAnimator->PlayAnimation(L"플레이어가만기본");
				state = PlayerState::Idle;
			}
		}
	}

	void PlayerScript::lookUp()
	{
  		/*auto an = GetOwner()->GetComponent<Animator>();
		bulletStartPos = { bulletStartPos.x, GetOwner()->GetComponent<Transform>()->GetPosition().y - 40 };
		if (an->GetActive()->getName() != L"플레이어기본총위상체" && direction == Vector2::Right)
		{
			an->PlayAnimation(L"플레이어기본총위상체");
		}
		else if (an->GetActive()->getName() != L"플레이어기본총위상체좌" && direction == Vector2::Left)
		{
			an->PlayAnimation(L"플레이어기본총위상체좌");
		}
		if (InputManager::getKey(VK_UP))
		{
			state = PlayerState::Lookup;
		}
		if (InputManager::getKeyUp(VK_UP))
		{
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
		}*/
	}

	void PlayerScript::lookUp_Attack()
	{
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render(HDC hDC)
	{
	}

	void PlayerScript::ShootBullet()
	{
		bulletOffset = Vector2::Rotate(Vector2::Right, direction) * 80 - Vector2(0, 30); //총까지 길이가 80정도
		auto tr = GetOwner()->GetComponent<Transform>();
		Vector2 bulletPosition = tr->GetPosition() + bulletOffset;
		//Vector2 mousePosition =
		//	app.getmousePosition(); //+ Vector2(position.x - app.getScreen().x / 2, position.y - app.getScreen().y / 2);

		std::random_device rd;
		std::mt19937 engine(rd());
		std::uniform_real_distribution<> urd(-1.0, 1.0);
		auto bullet = object::Instantiate<GameObject>(LayerType::Projectile
			, bulletPosition + Vector2::One * 8.0f * urd(engine));

		//Vector2 dest = (mousePosition - bulletStartPos).nomalize();
		/*float degree = acosf(Vector2::Dot(Vector2::Right, direction));
		if (Vector2::Cross(Vector2::Right, direction) < 0)
			degree = 2 * math::kPi - degree;*/
		auto bulletTr = bullet->GetComponent<Transform>();
		bulletTr->SetRotation(direction);

		auto sr = bullet->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"총알png"));

		bullet->AddComponent<BulletScript>();
		auto cd = bullet->AddComponent<CircleCollider2D>();
		cd->SetSize(Vector2::One * 0.2f);

		const auto& aniName = ownerAnimator->GetActive()->getName();

		if (aniName == L"플레이어가만총쏘는중상체")
		{
			count = 0;
		}
		else if(aniName == L"플레이어가만헤비쏘는중상체")
		{
			count++;
			if (count == 5) count = 0;
		}
		else if(aniName == L"플레이어가만쌍헤비쏘는중상체")
		{
			auto bulletTwo = object::Instantiate<GameObject>(LayerType::Projectile
				, bulletPosition + Vector2::One * 10.0f * urd(engine));
			auto bulletTwoTr = bulletTwo->GetComponent<Transform>();
			bulletTwoTr->SetRotation(direction);

			auto bulletTwoSr = bulletTwo->AddComponent<SpriteRenderer>();
			bulletTwoSr->SetTexture(Resources::Find<graphics::Texture>(L"총알png"));

			bulletTwo->AddComponent<BulletScript>();
			auto bulletTwoCd = bulletTwo->AddComponent<CircleCollider2D>();
			bulletTwoCd->SetSize(Vector2::One * 0.2f);
			count++;
			if (count == 5) count = 0;
		}
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