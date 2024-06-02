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
	//�������� �ʱ�ȭ�Ҷ�
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
	case PlayerLowerBodyScript::PlayerState::Jump:
		jump();
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
	auto rb = GetOwner()->GetComponent<RigidBody>();
	rb->SetMass(0);
}

void PlayerLowerBodyScript::OnCollisionStay(Collider* other)
{
	auto rb = GetOwner()->GetComponent<RigidBody>();
	rb->SetMass(0);
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
		an->PlayAnimation(L"�÷��̾����̵���ü");
	}
	if (InputManager::getKeyDown(VK_RIGHT))
	{
		state = PlayerState::Move;
		an->PlayAnimation(L"�÷��̾���̵���ü");
	}
	if (InputManager::getKeyDown(VK_OEM_COMMA))
	{
		state = PlayerState::Jump;
	}
	if (InputManager::getKeyDown(VK_DOWN))
	{
		state = PlayerState::Sit;
	}
	
	
}

void PlayerLowerBodyScript::move()
{
	auto tr = GetOwner()->GetComponent<Transform>();
	auto an = GetOwner()->GetComponent<Animator>();
	if (InputManager::getKey(VK_LEFT))
	{
		auto position = tr->GetPosition();
		if (an->GetActive()->getName() != L"�÷��̾����̵���ü")
		{
			an->PlayAnimation(L"�÷��̾����̵���ü");
		}
		tr->SetPosition({ position.x - Timer::getDeltaTime() * speed, position.y });
	}
	if (InputManager::getKey(VK_RIGHT))
	{
		auto position = tr->GetPosition();
		if (an->GetActive()->getName() != L"�÷��̾���̵���ü")
		{
			an->PlayAnimation(L"�÷��̾���̵���ü");
		}
		tr->SetPosition({ position.x + Timer::getDeltaTime() * speed, position.y });
	}
	if (InputManager::getKey(VK_UP))
	{
		state = PlayerState::Lookup;
	}
	if (InputManager::getKey(VK_DOWN))
	{
		state = PlayerState::Sit;
	}
	if (InputManager::getKeyDown(VK_OEM_COMMA))
	{
		state = PlayerState::Jump;
	}
	if (!InputManager::getKey(VK_RIGHT) && !InputManager::getKey(VK_LEFT))
	{
		an->PlayAnimation(L"�÷��̾����ü");
		state = PlayerState::Idle;
	}

}

void PlayerLowerBodyScript::down()
{
	//�̹��� �ɴ� �̹���
	auto an = GetOwner()->GetComponent<Animator>();
	if (an->GetActive()->getName()!=L"�÷��̾����"
		&& an->GetActive()->getName() != L"�÷��̾�ɱ����" 
		&& an->GetActive()->getName() != L"�÷��̾�ɱ��߰�" )
	{
		an->PlayAnimation(L"�÷��̾�ɱ����",false);
	}
	if (InputManager::getKey(VK_DOWN))
	{
		state = PlayerState::Sit;
	}
	if (InputManager::getKeyUp(VK_DOWN))
	{
		an->PlayAnimation(L"�÷��̾����ü", true);
		state = PlayerState::Idle;
	}
	if (InputManager::getKeyDown(VK_OEM_COMMA))
	{
		state = PlayerState::Jump;
	}
		
}

void PlayerLowerBodyScript::jump()
{
	//�̹��� �����ϴ� �̹��� ��ü �����϶��� ���� ����	
	auto rb = GetOwner()->GetComponent<RigidBody>();
	if (rb->GetVelocity() != Vector2::Zero)
	{
		rb->SetVelocity(Vector2(0, -100));
	}
	else {
		state = PlayerState::Idle;
	}
	
	
	
}

void PlayerLowerBodyScript::NextAnimation()
{
	auto an = GetOwner()->GetComponent<Animator>();
	if (an->GetActive()->getName()==L"�÷��̾�ɱ����")
	{
		an->PlayAnimation(L"�÷��̾�ɱ��߰�", false);
		return;
	}
	if (an->GetActive()->getName() == L"�÷��̾�ɱ��߰�")
	{
		an->PlayAnimation(L"�÷��̾����", true);
		return;
	}
	
}
