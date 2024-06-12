#include "ysEnemyScript.h"
#include <ysTransform.h>
#include <ysGameObject.h>
#include <ysObject.h>
#include <ysTimer.h>
#include <ysRenderer.h>
#include <YSapplication.h>
#include "ysRigidBody.h"
#include "ysBoxCollider2D.h"
#include "ysCircleCollider2D.h"
#include "ysCollisionManager.h"
#include "ysCollider.h"
#include "BulletScript.h"
#include <ysAnimator.h>

extern ys::Application app;

ys::EnemyScript::EnemyScript()
	: timer(0.0f), moveRight(false), hp(100), enemyType(EnemyType::Normal), enemyState(EnemyState::Idle)
{
}

ys::EnemyScript::~EnemyScript()
{
}

void ys::EnemyScript::Init()
{
}

void ys::EnemyScript::Update()
{
	switch (enemyType)
	{
	case ys::EnemyScript::EnemyType::Normal:
		
		break;
	case ys::EnemyScript::EnemyType::Strong:
		break;
	case ys::EnemyScript::EnemyType::Boss:
		break;
	default:
		break;
	}
	
}

void ys::EnemyScript::LateUpdate()
{
}

void ys::EnemyScript::Render(HDC hDC)
{
}

void ys::EnemyScript::OnCollisionEnter(Collider* other)
{
	if (other->GetOwner()->GetLayerType()==enums::LayerType::Block)
	{
		auto Blocktr = other->GetOwner()->GetComponent<Transform>();
		auto Blockcd = other->GetOwner()->GetComponent<BoxCollider2D>();

		auto playerRb = GetOwner()->GetComponent<RigidBody>();
		auto playerTr = GetOwner()->GetComponent<Transform>();
		auto playerCd = GetOwner()->GetComponent<BoxCollider2D>();

		float len = fabs((playerTr->GetPosition().y + playerCd->GetOffset().y)
			- (Blocktr->GetPosition().y + Blockcd->GetOffset().y));
		float scale = fabs(playerCd->GetSize().y * 100 / 2.0f);

		if (len < scale && playerRb->GetVelocity().y > 0)
		{
			auto playerPosition = playerTr->GetPosition();
			playerPosition.y -= scale - len;

			playerTr->SetPosition(playerPosition);
		}

		if (playerRb->GetVelocity().y > 0)
			playerRb->SetGround(true);
		else
			playerRb->SetGround(false);
	}


	if (other->GetOwner()->GetLayerType() == enums::LayerType::Particle) {
		int damage = other->GetOwner()->GetComponent<BulletScript>()->getDamage();
		hp -= damage;
		if (hp<0)
		{
			destroy();
		}
	}
}

void ys::EnemyScript::OnCollisionStay(Collider* other)
{
	
	if (other->GetOwner()->GetLayerType() == enums::LayerType::Block)
	{
		auto Blocktr = other->GetOwner()->GetComponent<Transform>();
		auto Blockcd = other->GetOwner()->GetComponent<BoxCollider2D>();

		auto playerRb = GetOwner()->GetComponent<RigidBody>();
		auto playerTr = GetOwner()->GetComponent<Transform>();
		auto playerCd = GetOwner()->GetComponent<BoxCollider2D>();

		float len = fabs((playerTr->GetPosition().y + playerCd->GetOffset().y)
			- (Blocktr->GetPosition().y + Blockcd->GetOffset().y));
		float scale = fabs(playerCd->GetSize().y * 100);

		if (len < scale && playerRb->GetVelocity().y > 0)
		{
			auto playerPosition = playerTr->GetPosition();
			playerPosition.y -= scale - len;

			playerTr->SetPosition(playerPosition);
		}

		if (playerRb->GetVelocity().y > 0)
			playerRb->SetGround(true);
		else
			playerRb->SetGround(false);
	}
	switch (enemyType)
	{
	case ys::EnemyScript::EnemyType::Normal:
		if (other->GetOwner()->GetLayerType() == enums::LayerType::Block)
		{
			auto this_bc = GetOwner()->GetComponent<BoxCollider2D>();
			auto this_tr = GetOwner()->GetComponent<Transform>();

			auto other_bc = other->GetOwner()->GetComponent<BoxCollider2D>();
			auto other_tr = other->GetOwner()->GetComponent<Transform>();
			if (moveRight)
			{
				auto other_RightPos = other_tr->GetPosition().x + other_bc->GetOffset().x + other_bc->GetSize().x * 100;
				auto this_Right = this_tr->GetPosition().x + this_bc->GetOffset().x + this_bc->GetSize().x * 100;
				if (other_RightPos < this_Right)
				{
					this_Right -= this_Right - other_RightPos;
					moveRight = false;
				}
			}
			else {
				auto other_Left = other_tr->GetPosition().x + other_bc->GetOffset().x;
				auto this_Left = this_tr->GetPosition().x + this_bc->GetOffset().x;
				if (this_Left<other_Left)
				{
					this_Left += other_Left - this_Left;
					moveRight = true;
				}
			}
			move();
		}
		break;
	case ys::EnemyScript::EnemyType::Strong:
		break;
	case ys::EnemyScript::EnemyType::Boss:
		break;
	default:
		break;
	}
	
}

void ys::EnemyScript::OnCollisionExit(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == enums::LayerType::Block)
	{
		auto rb = GetOwner()->GetComponent<RigidBody>();
		auto tr = GetOwner()->GetComponent<Transform>();

		rb->SetGround(false);
	}
}

void ys::EnemyScript::NexTAnimation()
{
	auto an = GetOwner()->GetComponent<Animator>();
	if (an->GetActive()->getName()==L"게_attack_기본1")
	{
		an->PlayAnimation(L"게_attack_기본2", false);
		return;
	}
	else if (an->GetActive()->getName() == L"게_attack_기본2")
	{
		an->PlayAnimation(L"게_idle", true);
		return;
	}
}

void ys::EnemyScript::destroy()
{
	ys::object::Destroy(GetOwner());
}



void ys::EnemyScript::move()
{
	auto rb = GetOwner()->GetComponent<RigidBody>();
	if (moveRight)
	{
		rb->SetVelocity({ 100,0 });
	}
	else
	{
		rb->SetVelocity({ -100,0 });
	}
}
