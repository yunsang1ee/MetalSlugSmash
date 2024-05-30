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
	default:
		break;
	}
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
	
	if (InputManager::getKeyDown(VK_LEFT))
	{
		state = PlayerState::Move;
		an->PlayAnimation(L"플레이어좌이동하체");
	}
	if (InputManager::getKeyDown(VK_RIGHT))
	{
		state = PlayerState::Move;
		an->PlayAnimation(L"플레이어우이동하체");
	}
	if (InputManager::getKeyDown(VK_UP))
	{
		state = PlayerState::Move;
	}
	if (InputManager::getKeyDown(VK_DOWN))
	{
		state = PlayerState::Move;
	}
	
}

void PlayerLowerBodyScript::move()
{
	auto tr = GetOwner()->GetComponent<Transform>();
	auto an = GetOwner()->GetComponent<Animator>();
	if (InputManager::getKey(VK_LEFT))
	{
		auto position = tr->GetPosition();
		if (an->GetActive()->getName() != L"플레이어좌이동하체")
		{
			an->PlayAnimation(L"플레이어좌이동하체");
		}
		tr->SetPosition({ position.x - Timer::getDeltaTime() * speed, position.y });
	}
	if (InputManager::getKey(VK_RIGHT))
	{
		auto position = tr->GetPosition();
		if (an->GetActive()->getName() != L"플레이어우이동하체")
		{
			an->PlayAnimation(L"플레이어우이동하체");
		}
		tr->SetPosition({ position.x + Timer::getDeltaTime() * speed, position.y });
	}
	if (InputManager::getKey(VK_UP))
	{
		auto position = tr->GetPosition();
		tr->SetPosition({ position.x, position.y - Timer::getDeltaTime() * speed });
	}
	if (InputManager::getKey(VK_DOWN))
	{
		auto position = tr->GetPosition();
		tr->SetPosition({ position.x, position.y + Timer::getDeltaTime() * speed });
	}
	if (!InputManager::getKey(VK_RIGHT) && !InputManager::getKey(VK_LEFT))
	{
		an->PlayAnimation(L"플레이어가만하체");
		state = PlayerState::Idle;
	}

}
