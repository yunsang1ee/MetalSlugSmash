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

PlayerLowerBodyScript::PlayerLowerBodyScript() :playerChest(nullptr), speed(300), state(PlayerState::Idle)
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
	
	switch (state)
	{
	case PlayerLowerBodyScript::PlayerState::Idle:
		idle();
		break;
	case PlayerLowerBodyScript::PlayerState::Move:
		move();
		break;
	case PlayerLowerBodyScript::PlayerState::Sit:
		down();
		break;
	case PlayerLowerBodyScript::PlayerState::Lookup:
		lookUp();
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
	if (InputManager::getKey(VK_OEM_COMMA))
	{
		jump();
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
		
		tr->SetRotation(kPi);
		rb->AddForce(Vector2::Left * speed);
		if (an->GetActive()->getName() != L"플레이어좌이동하체")
		{
			an->PlayAnimation(L"플레이어좌이동하체");
		}
		
	}
	if (InputManager::getKey(VK_RIGHT))
	{
		
		if (an->GetActive()->getName() != L"플레이어우이동하체")
		{
			an->PlayAnimation(L"플레이어우이동하체");
		}
		tr->SetRotation(kPi);
		rb->AddForce(Vector2::Right * speed);
	}
	
	if (InputManager::getKey(VK_DOWN))
	{
		state = PlayerState::Sit;
	}
	if (InputManager::getKeyDown(VK_OEM_COMMA))
	{
		jump();
	}
	if (!InputManager::getKey(VK_RIGHT) && !InputManager::getKey(VK_LEFT))
	{
		an->PlayAnimation(L"플레이어가만하체");
		state = PlayerState::Idle;
	}

}

void PlayerLowerBodyScript::down()
{
	//이미지 앉는 이미지
	auto an = GetOwner()->GetComponent<Animator>();
	if (an->GetActive()->getName()!=L"플레이어앉음"
		&& an->GetActive()->getName() != L"플레이어앉기시작" 
		&& an->GetActive()->getName() != L"플레이어앉기중간" )
	{
		an->PlayAnimation(L"플레이어앉기시작",false);
	}
	if (InputManager::getKey(VK_DOWN))
	{
		state = PlayerState::Sit;
	}
	if (InputManager::getKeyUp(VK_DOWN))
	{
		an->PlayAnimation(L"플레이어가만하체", true);
		state = PlayerState::Idle;
	}
	if (InputManager::getKey(VK_LEFT))
	{
		if (an->GetActive()->getName() == L"플레이어앉음")
		{
			an->PlayAnimation(L"플레이어앉음좌");
		}
	}
	if (InputManager::getKeyDown(VK_OEM_COMMA))
	{
		jump();
	}
		
}

void PlayerLowerBodyScript::jump()
{
	//이미지 점프하는 이미지 상체 무브일때는 무브 점프	
	auto rb = GetOwner()->GetComponent<RigidBody>();
	if (rb->IsGround())
	{
			auto velocity = rb->GetVelocity();
			velocity.y = -800.0f;
			rb->AddForce(Vector2::Up * 1000.0f);
			rb->SetVelocity(velocity);
			rb->SetGround(false);
	}
}

void PlayerLowerBodyScript::lookUp()
{
	
}

void PlayerLowerBodyScript::NextAnimation()
{
	auto an = GetOwner()->GetComponent<Animator>();
	if (an->GetActive()->getName()==L"플레이어앉기시작")
	{
		an->PlayAnimation(L"플레이어앉기중간", false);
		return;
	}
	if (an->GetActive()->getName() == L"플레이어앉기중간")
	{
		an->PlayAnimation(L"플레이어앉음", true);
		return;
	}
	if (an->GetActive()->getName()==L"플레이어앉기시작좌")
	{
		an->PlayAnimation(L"플레이어앉기중간좌", false);
		return;
	}
	if (an->GetActive()->getName() == L"플레이어앉기중간좌")
	{
		an->PlayAnimation(L"플레이어앉음좌", true);
		return;
	}
	
}
