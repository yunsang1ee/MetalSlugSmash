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
#include <ysResources.h>

extern ys::Application app;

ys::EnemyScript::EnemyScript()
	: timer(0.0f), moveRight(false), hp(100), enemyType(EnemyType::Normal), enemyState(EnemyState::Idle), death(false)
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

	if (!death)
	{
		if (other->GetOwner()->GetLayerType() == enums::LayerType::Projectile) {
			int damage = other->GetOwner()->GetComponent<BulletScript>()->getDamage();
			hp -= damage;
			if (hp < 0)
			{
				destroy();
			}
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
	if (!death)
	{
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
					if (this_Left < other_Left)
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
	auto nowName = an->GetActive()->getName();
	if (an->GetActive()->getName()==L"��_attack_�⺻1")
	{
		an->PlayAnimation(L"��_attack_�⺻2", false);
		return;
	}
	else if (an->GetActive()->getName() == L"��_attack_�⺻2")
	{
		an->PlayAnimation(L"��_idle", true);
		return;
	}

	if (!moveRight)
	{
		if (nowName == L"��_death_1")
		{
			an->PlayAnimation(L"��_death_2", false);
			return;
		}
		else if (nowName == L"��_death_2")
		{
			an->PlayAnimation(L"��_death_3", false);
			return;
		}
		else if (nowName == L"��_death_3")
		{
			an->PlayAnimation(L"��_death_4", false);
			return;
		}
		else if (nowName == L"��_death_4")
		{
			ys::object::Destroy(GetOwner());
		}
	}
	else if (moveRight)
	{
		if (nowName == L"��_death_1_��")
		{
			an->PlayAnimation(L"��_death_2_��", false);
			return;
		}
		else if (nowName == L"��_death_2_��")
		{
			an->PlayAnimation(L"��_death_3_��", false);
			return;
		}
		else if (nowName == L"��_death_3_��")
		{
			an->PlayAnimation(L"��_death_4_��", false);
			return;
		}
		else if (nowName == L"��_death_4_��")
		{
			ys::object::Destroy(GetOwner());
		}
	}
	
}

void ys::EnemyScript::IsAdd()
{
	auto an = GetOwner()->AddComponent<Animator>();
	auto rb = GetOwner()->AddComponent<RigidBody>();
	auto cd = GetOwner()->AddComponent<BoxCollider2D>();
	auto es = GetOwner()->GetComponent<EnemyScript>();

	cd->SetOffset(Vector2(-30, -25));
	cd->SetSize(Vector2(1.5f, 1.25f));
	an->CrateAnimation(L"��_idle", Resources::Find<graphics::Texture>(L"��_idle")
		, Vector2(0, 0)
		, Vector2(200, 150)
		, Vector2(-60, -50), 7, 0.1f, true);
	an->CrateAnimation(L"��_idle_��", Resources::Find<graphics::Texture>(L"��_idle_��")
		, Vector2(0, 0)
		, Vector2(200, 150)
		, Vector2(-60, -50), 7, 0.1f);

	an->CrateAnimation(L"��_walk", Resources::Find<graphics::Texture>(L"��_walk")
		, Vector2(0, 0)
		, Vector2(200, 146)
		, Vector2(-60, -50), 7, 0.1f, true);
	an->CrateAnimation(L"��_walk_��", Resources::Find<graphics::Texture>(L"��_walk_��")
		, Vector2(0, 0)
		, Vector2(200, 146)
		, Vector2(-60, -50), 7, 0.1f);

	an->CrateAnimation(L"��_attack_�⺻1", Resources::Find<graphics::Texture>(L"��_attack")
		, Vector2(50, 0)
		, Vector2(177, 170)
		, Vector2(-60, -50), 5, 0.1f, true);
	an->CrateAnimation(L"��_attack_�⺻2", Resources::Find<graphics::Texture>(L"��_attack")
		, Vector2(938, 0)
		, Vector2(243, 170)
		, Vector2(-60, -50), 4, 0.1f, true);
	an->CrateAnimation(L"��_attack_��_�⺻1", Resources::Find<graphics::Texture>(L"��_attack_��")
		, Vector2(50, 0)
		, Vector2(177, 170)
		, Vector2(-60, -50), 5, 0.1f);
	an->CrateAnimation(L"��_attack_��_�⺻2", Resources::Find<graphics::Texture>(L"��_attack_��")
		, Vector2(938, 0)
		, Vector2(243, 170)
		, Vector2(-60, -50), 4, 0.1f);


	an->CrateAnimation(L"��_death_1", Resources::Find<graphics::Texture>(L"��_death_1")
		, Vector2(10, 0)
		, Vector2(320, 165)
		, Vector2(-70, -65), 7, 0.1f, true);
	an->CrateAnimation(L"��_death_1_��", Resources::Find<graphics::Texture>(L"��_death_1_��")
		, Vector2(10, 0)
		, Vector2(320, 165)
		, Vector2(-70, -65), 7, 0.1f);

	an->CrateAnimation(L"��_death_2", Resources::Find<graphics::Texture>(L"��_death_2")
		, Vector2(77, 0)
		, Vector2(245, 184)
		, Vector2(-60, -75), 6, 0.1f, true);
	an->CrateAnimation(L"��_death_2_��", Resources::Find<graphics::Texture>(L"��_death_2_��")
		, Vector2(77, 0)
		, Vector2(245, 184)
		, Vector2(-60, -55), 6, 0.1f);

	an->CrateAnimation(L"��_death_3", Resources::Find<graphics::Texture>(L"��_death_3")
		, Vector2(0, 0)
		, Vector2(353, 190)
		, Vector2(-90, -90), 7, 0.1f, true);
	an->CrateAnimation(L"��_death_3_��", Resources::Find<graphics::Texture>(L"��_death_3_��")
		, Vector2(0, 0)
		, Vector2(353, 190)
		, Vector2(-90, -90), 7, 0.1f);
	an->CrateAnimation(L"��_death_4", Resources::Find<graphics::Texture>(L"��_death_4")
		, Vector2(50, 0)
		, Vector2(280, 182)
		, Vector2(-100, -70), 3, 0.1f, true);
	an->CrateAnimation(L"��_death_4_��", Resources::Find<graphics::Texture>(L"��_death_4_��")
		, Vector2(50, 0)
		, Vector2(280, 182)
		, Vector2(-100, -70), 3, 0.1f);


	an->GetCompleteEvent(L"��_attack_�⺻1") = std::bind(&EnemyScript::NexTAnimation, es);
	an->GetCompleteEvent(L"��_attack_�⺻2") = std::bind(&EnemyScript::NexTAnimation, es);
	an->GetCompleteEvent(L"��_attack_��_�⺻1") = std::bind(&EnemyScript::NexTAnimation, es);
	an->GetCompleteEvent(L"��_attack_��_�⺻2") = std::bind(&EnemyScript::NexTAnimation, es);

	an->GetCompleteEvent(L"��_death_1") = std::bind(&EnemyScript::NexTAnimation, es);
	an->GetCompleteEvent(L"��_death_2") = std::bind(&EnemyScript::NexTAnimation, es);
	an->GetCompleteEvent(L"��_death_3") = std::bind(&EnemyScript::NexTAnimation, es);
	an->GetCompleteEvent(L"��_death_4") = std::bind(&EnemyScript::NexTAnimation, es);

	an->GetCompleteEvent(L"��_death_1_��") = std::bind(&EnemyScript::NexTAnimation, es);
	an->GetCompleteEvent(L"��_death_2_��") = std::bind(&EnemyScript::NexTAnimation, es);
	an->GetCompleteEvent(L"��_death_3_��") = std::bind(&EnemyScript::NexTAnimation, es);
	an->GetCompleteEvent(L"��_death_4_��") = std::bind(&EnemyScript::NexTAnimation, es);

	an->PlayAnimation(L"��_walk_��", true);
}

void ys::EnemyScript::destroy()
{
	auto an = GetOwner()->GetComponent<Animator>();
	an->PlayAnimation(L"��_death_1", false);
	death = true;
}



void ys::EnemyScript::move()
{
	auto rb = GetOwner()->GetComponent<RigidBody>();
	auto an = GetOwner()->GetComponent<Animator>();
	if (moveRight)
	{
		if (an->GetActive()->getName()!=L"��_walk")
		{
			an->PlayAnimation(L"��_walk", true);
		}
		
		rb->SetVelocity({ 100,0 });
	}
	else
	{

		if (an->GetActive()->getName() != L"��_walk_��")
		{
			an->PlayAnimation(L"��_walk_��", true);
		}
		rb->SetVelocity({ -100,0 });
	}
}
