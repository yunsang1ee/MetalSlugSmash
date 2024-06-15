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
	//�������� �ʱ�ȭ�Ҷ�
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
		an->PlayAnimation(L"�÷��̾����̵���ü");
	}
	if (InputManager::getKey(VK_RIGHT))
	{
		state = PlayerState::Move;
		an->PlayAnimation(L"�÷��̾���̵���ü");
	}
	if (InputManager::getKey(VK_OEM_COMMA) && GetOwner()->GetComponent<RigidBody>()->IsGround())
	{
		jump();
		if (Direction == Vector2::Right)
			an->PlayAnimation(L"�÷��̾�_����_��ü", true);
		else
			an->PlayAnimation(L"�÷��̾�_����_��ü��", true);
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
		if (an->GetActive()->getName() != L"�÷��̾����̵���ü")
		{
			an->PlayAnimation(L"�÷��̾����̵���ü");
		}
		Direction = Vector2::Left;
		rb->AddForce(Vector2::Left * speed);
	}
	if (InputManager::getKey(VK_RIGHT))
	{
		if (an->GetActive()->getName() != L"�÷��̾���̵���ü")
		{
			an->PlayAnimation(L"�÷��̾���̵���ü");
		}
		Direction = Vector2::Right;
		rb->AddForce(Vector2::Right * speed);
	}
	if (InputManager::getKeyDown(VK_UP))
	{
		if (Direction==Vector2::Right)
		{
			an->PlayAnimation(L"�÷��̾�������ü", true);
		}
		else {
			an->PlayAnimation(L"�÷��̾�������ü", true);
		}
		state = PlayerState::Lookup;
	}
	if (InputManager::getKey(VK_DOWN))
	{
		if (Direction==Vector2::Right)
		{
			an->PlayAnimation(L"�÷��̾�ɱ����", false);
		}
		else {
			an->PlayAnimation(L"�÷��̾�ɱ������", false);
		}
		state = PlayerState::Sit;
	}
	if (InputManager::getKey(VK_OEM_COMMA) && GetOwner()->GetComponent<RigidBody>()->IsGround())
	{
		if (Direction ==Vector2::Right)
			an->PlayAnimation(L"�÷��̾�_�̵�_����_��ü", true);
		else
			an->PlayAnimation(L"�÷��̾�_�̵�_����_��ü��", true);
		jump();
		state = PlayerState::MoveJump;
	}
	if (!InputManager::getKey(VK_RIGHT) && !InputManager::getKey(VK_LEFT))
	{
		auto rb = GetOwner()->GetComponent<RigidBody>();
		rb->SetVelocity(Vector2(0.0f, rb->GetVelocity().y));
		if (Direction == Vector2::Left)
		{
			an->PlayAnimation(L"�÷��̾����ü��");
		}
		else {
			an->PlayAnimation(L"�÷��̾����ü");
		}
		state = PlayerState::Idle;
	}

}

void PlayerLowerBodyScript::sit()
{
	//�̹��� �ɴ� �̹���
	auto an = GetOwner()->GetComponent<Animator>();
	auto rb = GetOwner()->GetComponent<RigidBody>();
	auto animationName = an->GetActive()->getName();
	if (InputManager::getKey(VK_DOWN))
	{
		if (Direction == Vector2::Right)
		{
			if (animationName != L"�÷��̾����" && animationName != L"�÷��̾�_����_�̵�" && animationName != L"�÷��̾�_����_����")
			{
				an->PlayAnimation(L"�÷��̾����", true);
			}
		}
		else
		{
			if (animationName != L"�÷��̾������" && animationName != L"�÷��̾�_����_�̵���" && animationName != L"�÷��̾�_����_������")
			{
				an->PlayAnimation(L"�÷��̾������", true);
			}
		}
	}
	if (InputManager::getKeyDown(VK_OEM_COMMA))
	{
		if (Direction == Vector2::Right)
		{
			an->PlayAnimation(L"�÷��̾�_�����̵�",false);
			rb->SetVelocity(Vector2(300.0f, rb->GetVelocity().y));
		}
		else
		{
			an->PlayAnimation(L"�÷��̾�_�����̵���",false);
			rb->SetVelocity(Vector2(-300.0f, rb->GetVelocity().y));
		}
		
		state = PlayerState::Slide;
		return;
	}

	if (InputManager::getKey(VK_LEFT))
	{
		if (animationName != L"�÷��̾�_����_�̵���")
		{
			an->PlayAnimation(L"�÷��̾�_����_�̵���", true);
		}
		state = PlayerState::Sit;
		rb->SetVelocity(Vector2::Left * speed/2);
		Direction = Vector2::Left;
	}
	else if (InputManager::getKey(VK_RIGHT))
	{
		if (animationName != L"�÷��̾�_����_�̵�")
		{
			an->PlayAnimation(L"�÷��̾�_����_�̵�", true);
		}
		state = PlayerState::Sit;	
		rb->SetVelocity(Vector2::Right * speed/2);
		Direction = Vector2::Right;
	}
	else if (InputManager::getKeyDown(VK_SPACE))
	{
		if (Direction == Vector2::Right)
		{
			an->PlayAnimation(L"�÷��̾�_����_����",false);
		}
		else
		{
			an->PlayAnimation(L"�÷��̾�_����_������",false);
		}
		state = PlayerState::SitShoot;
		return;
	}
	
	if (InputManager::getKeyUp(VK_RIGHT))
	{
		rb->SetVelocity(Vector2(0.0f, rb->GetVelocity().y));
		an->PlayAnimation(L"�÷��̾����", true);
	}
	if (InputManager::getKeyUp(VK_LEFT))
	{
		rb->SetVelocity(Vector2(0.0f, rb->GetVelocity().y));
		an->PlayAnimation(L"�÷��̾������", true);
	}
	
	


	if (InputManager::getKeyUp(VK_DOWN))
	{
		if (Direction == Vector2::Right)
		{
			an->PlayAnimation(L"�÷��̾����ü", true);
		}
		else
		{
			an->PlayAnimation(L"�÷��̾����ü��", true);
		}

		state = PlayerState::Idle;
	}
		
}
void PlayerLowerBodyScript::jump()
{
	//�̹��� �����ϴ� �̹��� ��ü �����϶��� ���� ����	
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
			an->PlayAnimation(L"�÷��̾����ü");
		}
		else
		{
			an->PlayAnimation(L"�÷��̾����ü��");
		}
		state = PlayerState::Idle;
	}
	else if (InputManager::getKeyDown(VK_LEFT))
	{
		an->PlayAnimation(L"�÷��̾�_�̵�_����_��ü��", true);
		Direction = Vector2::Left;
		state = PlayerState::MoveJump;
	}
	else if (InputManager::getKeyDown(VK_RIGHT))
	{
		an->PlayAnimation(L"�÷��̾�_�̵�_����_��ü", true);
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
				an->PlayAnimation(L"�÷��̾���̵���ü");
			}
			else
			{
				an->PlayAnimation(L"�÷��̾����̵���ü");
			}
			state = PlayerState::Move;
		}
		else
		{
			if (Direction==Vector2::Right)
			{
				an->PlayAnimation(L"�÷��̾����ü");
			}
			else
			{
				an->PlayAnimation(L"�÷��̾����ü��");
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
		an->PlayAnimation(L"�÷��̾����ü", true);
		state = PlayerState::Idle;
	}
	if (InputManager::getKey(VK_LEFT))
	{
		if (an->GetActive()->getName()!=L"�÷��̾����̵���ü")
		{
			an->PlayAnimation(L"�÷��̾����̵���ü", true);
		}
		Direction = Vector2::Left;
		state = PlayerState::Move;
	}
	else if (InputManager::getKeyDown(VK_RIGHT))
	{
		if (an->GetActive()->getName() != L"�÷��̾���̵���ü")
		{
			an->PlayAnimation(L"�÷��̾���̵���ü", true);
		}
		Direction = Vector2::Right;
		state = PlayerState::Move;
	}
	else if (InputManager::getKey(VK_UP))
	{
		if (Direction==Vector2::Right)
		{
			if (an->GetActive()->getName() != L"�÷��̾�������ü")
			{
				an->PlayAnimation(L"�÷��̾�������ü");
			}
		}
		else
		{
			if (an->GetActive()->getName() != L"�÷��̾�������ü")
			{
				an->PlayAnimation(L"�÷��̾�������ü");
			}
		}
		
	}
	if (InputManager::getKey(VK_DOWN))
	{
		//�Ʒ����� ��ü����
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
				an->PlayAnimation(L"�÷��̾����");
			}
			else
			{
				an->PlayAnimation(L"�÷��̾������");
			}
			
			state = PlayerState::Sit;
			return;
		}
	}
	



	if (InputManager::getKeyDown(VK_SPACE)&&rb->GetVelocity() != Vector2(0, 0))
	{
		if (Direction==Vector2::Right)
		{
			an->PlayAnimation(L"�÷��̾�_�����̵�_�⺻��_����",false);
		}
		else
		{
			an->PlayAnimation(L"�÷��̾�_�����̵�_�⺻��_������",false);
		}
		
	}
	if (rb->GetVelocity() == Vector2(0, 0))
	{
		if (Direction == Vector2::Right)
		{
			an->PlayAnimation(L"�÷��̾����ü");
		}
		else
		{
			an->PlayAnimation(L"�÷��̾����ü��");
		}
		state = PlayerState::Idle;
	}
	
}
void PlayerLowerBodyScript::NextSitAnimation()
{
	auto an = GetOwner()->GetComponent<Animator>();
	auto animationName = an->GetActive()->getName();

	if (animationName == L"�÷��̾�ɱ����")
	{
		an->PlayAnimation(L"�÷��̾�ɱ��߰�", false);
		return;
	}
	if (animationName == L"�÷��̾�ɱ��߰�")
	{
		an->PlayAnimation(L"�÷��̾����", true);
		return;
	}
	if (animationName == L"�÷��̾�ɱ������")
	{
		an->PlayAnimation(L"�÷��̾�ɱ��߰���", false);
		return;
	}
	if (animationName == L"�÷��̾�ɱ��߰���")
	{
		an->PlayAnimation(L"�÷��̾������", true);
		return;
	}
	if (animationName == L"�÷��̾�_����_����")
	{
		an->PlayAnimation(L"�÷��̾����", true);
		state = PlayerState::Sit;
		return;
	}
	if (animationName == L"�÷��̾�_����_������")
	{
		an->PlayAnimation(L"�÷��̾������",true);
		state = PlayerState::Sit;
		return;
	}

}
