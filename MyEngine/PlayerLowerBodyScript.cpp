#include "PlayerLowerBodyScript.h"
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

PlayerLowerBodyScript::PlayerLowerBodyScript() :playerChest(nullptr), speed(3000), state(PlayerState::Idle)
{
	
}
PlayerLowerBodyScript::~PlayerLowerBodyScript()
{
}

void PlayerLowerBodyScript::Init()
{
	//스테이지 초기화할때
}

void PlayerLowerBodyScript::Update()
{
	auto tr = GetOwner()->GetComponent<Transform>();
	an = GetOwner()->GetComponent<Animator>();
	switch (state)
	{
	case PlayerLowerBodyScript::PlayerState::Idle:
		idle();
		break;
	case PlayerLowerBodyScript::PlayerState::Move:
		move();
		break;
	case PlayerLowerBodyScript::PlayerState::Sit:
		sit();
		break;
	case PlayerLowerBodyScript::PlayerState::Lookup:
		lookUp();
		break;
	case PlayerLowerBodyScript::PlayerState::IdleJump:
		idleJump();
		break;
	case PlayerLowerBodyScript::PlayerState::MoveJump:
		moveJump();
		break;
	case PlayerLowerBodyScript::PlayerState::Slide:
		slide();
		break;
	default:
		break;
	}
	auto rb = GetOwner()->GetComponent<RigidBody>();
	
}



void PlayerLowerBodyScript::LateUpdate()
{
}

void PlayerLowerBodyScript::Render(HDC hDC)
{
}

void PlayerLowerBodyScript::OnCollisionEnter(Collider* other)
{
	
}

void PlayerLowerBodyScript::OnCollisionStay(Collider* other)
{
	
}

void PlayerLowerBodyScript::OnCollisionExit(Collider* other)
{
}

void PlayerLowerBodyScript::idle()
{
	auto an = GetOwner()->GetComponent<Animator>();
	auto rb = GetOwner()->GetComponent<RigidBody>();
	

	if (InputManager::getKey(VK_LEFT))
	{
		state = PlayerState::Move;
		an->PlayAnimation(L"플레이어좌이동하체");
	}
	if (InputManager::getKey(VK_RIGHT))
	{
		state = PlayerState::Move;
		an->PlayAnimation(L"플레이어우이동하체");
	}
	if (InputManager::getKey(VK_OEM_COMMA) && GetOwner()->GetComponent<RigidBody>()->IsGround())
	{
		jump();
		if (Direction == Vector2::Right)
			an->PlayAnimation(L"플레이어_점프_하체", true);
		else
			an->PlayAnimation(L"플레이어_점프_하체좌", true);
		state = PlayerState::IdleJump;
	}
	if (InputManager::getKey(VK_UP))
	{
		state = PlayerState::Lookup;
	}
	if (InputManager::getKey(VK_DOWN))
	{
		state = PlayerState::Sit;
	}
	
	
}

void PlayerLowerBodyScript::move()
{
	auto tr = GetOwner()->GetComponent<Transform>();
	auto an = GetOwner()->GetComponent<Animator>();
	auto rb = GetOwner()->GetComponent<RigidBody>();
	if (InputManager::getKey(VK_LEFT))
	{
		if (an->GetActive()->getName() != L"플레이어좌이동하체")
		{
			an->PlayAnimation(L"플레이어좌이동하체");
		}
		Direction = Vector2::Left;
		rb->AddForce(Vector2::Left * speed);
	}
	if (InputManager::getKey(VK_RIGHT))
	{
		if (an->GetActive()->getName() != L"플레이어우이동하체")
		{
			an->PlayAnimation(L"플레이어우이동하체");
		}
		Direction = Vector2::Right;
		rb->AddForce(Vector2::Right * speed);
	}
	if (InputManager::getKeyDown(VK_UP))
	{
		if (Direction==Vector2::Right)
		{
			an->PlayAnimation(L"플레이어위우하체", true);
		}
		else {
			an->PlayAnimation(L"플레이어위좌하체", true);
		}
		state = PlayerState::Lookup;
	}
	if (InputManager::getKey(VK_DOWN))
	{
		if (Direction==Vector2::Right)
		{
			an->PlayAnimation(L"플레이어앉기시작", false);
		}
		else {
			an->PlayAnimation(L"플레이어앉기시작좌", false);
		}
		state = PlayerState::Sit;
	}
	if (InputManager::getKey(VK_OEM_COMMA) && GetOwner()->GetComponent<RigidBody>()->IsGround())
	{
		if (Direction ==Vector2::Right)
			an->PlayAnimation(L"플레이어_이동_점프_하체", true);
		else
			an->PlayAnimation(L"플레이어_이동_점프_하체좌", true);
		jump();
		state = PlayerState::MoveJump;
	}
	if (!InputManager::getKey(VK_RIGHT) && !InputManager::getKey(VK_LEFT))
	{
		auto rb = GetOwner()->GetComponent<RigidBody>();
		rb->SetVelocity(Vector2(0.0f, rb->GetVelocity().y));
		if (Direction == Vector2::Left)
		{
			an->PlayAnimation(L"플레이어가만하체좌");
		}
		else {
			an->PlayAnimation(L"플레이어가만하체");
		}
		state = PlayerState::Idle;
	}

}

void PlayerLowerBodyScript::sit()
{
	//이미지 앉는 이미지
	auto an = GetOwner()->GetComponent<Animator>();
	auto rb = GetOwner()->GetComponent<RigidBody>();
	auto animationName = an->GetActive()->getName();
	if (InputManager::getKey(VK_DOWN))
	{
		if (Direction == Vector2::Right)
		{
			if (animationName != L"플레이어앉음" && animationName != L"플레이어_앉음_이동" && animationName != L"플레이어_앉음_공격")
			{
				an->PlayAnimation(L"플레이어앉음", true);
			}
		}
		else
		{
			if (animationName != L"플레이어앉음좌" && animationName != L"플레이어_앉음_이동좌" && animationName != L"플레이어_앉음_공격좌")
			{
				an->PlayAnimation(L"플레이어앉음좌", true);
			}
		}
	}
	if (InputManager::getKeyDown(VK_OEM_COMMA))
	{
		if (Direction == Vector2::Right)
		{
			an->PlayAnimation(L"플레이어_슬라이딩",false);
			rb->SetVelocity(Vector2(300.0f, rb->GetVelocity().y));
		}
		else
		{
			an->PlayAnimation(L"플레이어_슬라이딩좌",false);
			rb->SetVelocity(Vector2(-300.0f, rb->GetVelocity().y));
		}
		
		state = PlayerState::Slide;
		return;
	}

	if (InputManager::getKey(VK_LEFT))
	{
		if (animationName != L"플레이어_앉음_이동좌")
		{
			an->PlayAnimation(L"플레이어_앉음_이동좌", true);
		}
		state = PlayerState::Sit;
		rb->SetVelocity(Vector2::Left * speed/2);
		Direction = Vector2::Left;
	}
	else if (InputManager::getKey(VK_RIGHT))
	{
		if (animationName != L"플레이어_앉음_이동")
		{
			an->PlayAnimation(L"플레이어_앉음_이동", true);
		}
		state = PlayerState::Sit;	
		rb->SetVelocity(Vector2::Right * speed/2);
		Direction = Vector2::Right;
	}
	else if (InputManager::getKeyDown(VK_SPACE))
	{
		if (Direction == Vector2::Right)
		{
			an->PlayAnimation(L"플레이어_앉음_공격",false);
		}
		else
		{
			an->PlayAnimation(L"플레이어_앉음_공격좌",false);
		}
		state = PlayerState::SitShoot;
		return;
	}
	
	if (InputManager::getKeyUp(VK_RIGHT))
	{
		rb->SetVelocity(Vector2(0.0f, rb->GetVelocity().y));
		an->PlayAnimation(L"플레이어앉음", true);
	}
	if (InputManager::getKeyUp(VK_LEFT))
	{
		rb->SetVelocity(Vector2(0.0f, rb->GetVelocity().y));
		an->PlayAnimation(L"플레이어앉음좌", true);
	}
	
	


	if (InputManager::getKeyUp(VK_DOWN))
	{
		if (Direction == Vector2::Right)
		{
			an->PlayAnimation(L"플레이어가만하체", true);
		}
		else
		{
			an->PlayAnimation(L"플레이어가만하체좌", true);
		}

		state = PlayerState::Idle;
	}
		
}
void PlayerLowerBodyScript::jump()
{
	//이미지 점프하는 이미지 상체 무브일때는 무브 점프	
	auto rb = GetOwner()->GetComponent<RigidBody>();
	auto velocity = rb->GetVelocity();
	if (rb->IsGround())
	{
		velocity.y = -1200.0f;
		//rb->AddForce(Vector2::Up * 1000.0f);
		rb->SetVelocity(velocity);
		rb->SetGround(false);
	}
}
void PlayerLowerBodyScript::idleJump()
{
	auto rb = GetOwner()->GetComponent<RigidBody>();
	auto animationName = an->GetActive()->getName();
	if (rb->IsGround())
	{
		if (Direction == Vector2::Right)
		{
			an->PlayAnimation(L"플레이어가만하체");
		}
		else
		{
			an->PlayAnimation(L"플레이어가만하체좌");
		}
		state = PlayerState::Idle;
	}
	else if (InputManager::getKeyDown(VK_LEFT))
	{
		an->PlayAnimation(L"플레이어_이동_점프_하체좌", true);
		Direction = Vector2::Left;
		state = PlayerState::MoveJump;
	}
	else if (InputManager::getKeyDown(VK_RIGHT))
	{
		an->PlayAnimation(L"플레이어_이동_점프_하체", true);
		Direction = Vector2::Right;
		state = PlayerState::MoveJump;
	}
}
void PlayerLowerBodyScript::moveJump()
{
	auto rb = GetOwner()->GetComponent<RigidBody>();
	if (rb->IsGround())
	{
		if (InputManager::getKey(VK_RIGHT)|| InputManager::getKey(VK_LEFT))
		{
			if (Direction == Vector2::Right)
			{
				an->PlayAnimation(L"플레이어우이동하체");
			}
			else
			{
				an->PlayAnimation(L"플레이어좌이동하체");
			}
			state = PlayerState::Move;
		}
		else
		{
			if (Direction==Vector2::Right)
			{
				an->PlayAnimation(L"플레이어가만하체");
			}
			else
			{
				an->PlayAnimation(L"플레이어가만하체좌");
			}
			state = PlayerState::Idle;
		}
		
	}
	else if (InputManager::getKey(VK_RIGHT))
	{
		rb->AddForce(Vector2::Right * speed);
		Direction = Vector2::Right;
	}
	else if (InputManager::getKey(VK_LEFT))
	{
		rb->AddForce(Vector2::Left * speed);
		Direction = Vector2::Left;
	}

	if (InputManager::getKeyUp(VK_LEFT))
	{
		rb->SetVelocity(Vector2(0.0f, rb->GetVelocity().y));
	}
	else if (InputManager::getKeyUp(VK_RIGHT))
	{
		rb->SetVelocity(Vector2(0.0f, rb->GetVelocity().y));
	}

	
}
void PlayerLowerBodyScript::lookUp()
{
	auto an = GetOwner()->GetComponent<Animator>();
	if (InputManager::getKeyUp(VK_UP))
	{
		an->PlayAnimation(L"플레이어가만하체", true);
		state = PlayerState::Idle;
	}
	if (InputManager::getKey(VK_LEFT))
	{
		if (an->GetActive()->getName()!=L"플레이어좌이동하체")
		{
			an->PlayAnimation(L"플레이어좌이동하체", true);
		}
		Direction = Vector2::Left;
		state = PlayerState::Move;
	}
	else if (InputManager::getKeyDown(VK_RIGHT))
	{
		if (an->GetActive()->getName() != L"플레이어우이동하체")
		{
			an->PlayAnimation(L"플레이어우이동하체", true);
		}
		Direction = Vector2::Right;
		state = PlayerState::Move;
	}
	else if (InputManager::getKey(VK_UP))
	{
		if (Direction==Vector2::Right)
		{
			if (an->GetActive()->getName() != L"플레이어위우하체")
			{
				an->PlayAnimation(L"플레이어위우하체");
			}
		}
		else
		{
			if (an->GetActive()->getName() != L"플레이어위좌하체")
			{
				an->PlayAnimation(L"플레이어위좌하체");
			}
		}
		
	}
	if (InputManager::getKey(VK_DOWN))
	{
		//아래보기 상체에서
	}
	if (InputManager::getKeyDown(VK_OEM_COMMA))
	{
		idleJump();
	}
	
}
void PlayerLowerBodyScript::slide()
{
	auto an = GetOwner()->GetComponent<Animator>();
	auto rb = GetOwner()->GetComponent<RigidBody>();
	
	if (InputManager::getKey(VK_DOWN))
	{
		if (rb->GetVelocity() == Vector2(0, 0))
		{
			if (Direction==Vector2::Right)
			{
				an->PlayAnimation(L"플레이어앉음");
			}
			else
			{
				an->PlayAnimation(L"플레이어앉음좌");
			}
			
			state = PlayerState::Sit;
			return;
		}
	}
	



	if (InputManager::getKeyDown(VK_SPACE)&&rb->GetVelocity() != Vector2(0, 0))
	{
		if (Direction==Vector2::Right)
		{
			an->PlayAnimation(L"플레이어_슬라이딩_기본총_공격",false);
		}
		else
		{
			an->PlayAnimation(L"플레이어_슬라이딩_기본총_공격좌",false);
		}
		
	}
	if (rb->GetVelocity() == Vector2(0, 0))
	{
		if (Direction == Vector2::Right)
		{
			an->PlayAnimation(L"플레이어가만하체");
		}
		else
		{
			an->PlayAnimation(L"플레이어가만하체좌");
		}
		state = PlayerState::Idle;
	}
	
}
void PlayerLowerBodyScript::NextSitAnimation()
{
	auto an = GetOwner()->GetComponent<Animator>();
	auto animationName = an->GetActive()->getName();

	if (animationName == L"플레이어앉기시작")
	{
		an->PlayAnimation(L"플레이어앉기중간", false);
		return;
	}
	if (animationName == L"플레이어앉기중간")
	{
		an->PlayAnimation(L"플레이어앉음", true);
		return;
	}
	if (animationName == L"플레이어앉기시작좌")
	{
		an->PlayAnimation(L"플레이어앉기중간좌", false);
		return;
	}
	if (animationName == L"플레이어앉기중간좌")
	{
		an->PlayAnimation(L"플레이어앉음좌", true);
		return;
	}
	if (animationName == L"플레이어_앉음_공격")
	{
		an->PlayAnimation(L"플레이어앉음", true);
		state = PlayerState::Sit;
		return;
	}
	if (animationName == L"플레이어_앉음_공격좌")
	{
		an->PlayAnimation(L"플레이어앉음좌",true);
		state = PlayerState::Sit;
		return;
	}

}
