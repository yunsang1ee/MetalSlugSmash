#include "BlockScript.h"
#include<ysGameObject.h>
#include<ysBoxCollider2D.h>
#include<ysSceneManager.h>
#include<ysScene.h>
#include <ysRigidBody.h>
#include <ysTransform.h>
#include <ysCircleCollider2D.h>
#include<ysCollisionManager.h>
using namespace ys;
BlockScript::BlockScript()
{
}

BlockScript::~BlockScript()
{
}

void BlockScript::Init()
{
}

void BlockScript::Update()
{
	
}

void BlockScript::LateUpdate()
{
}

void BlockScript::Render(HDC hDC)
{
}

void BlockScript::OnCollisionEnter(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == enums::LayerType::playerLowerBody)
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto cd = GetOwner()->GetComponent<BoxCollider2D>();
		
		auto playerRb = other->GetOwner()->GetComponent<RigidBody>();
		auto playerTr = other->GetOwner()->GetComponent<Transform>();
		auto playerCd = other->GetOwner()->GetComponent<BoxCollider2D>();

		float len = fabs(playerTr->GetPosition().y - tr->GetPosition().y);
		//이렇게 말고 콜라이더의 겹친 값만큼 보정해줘야지
		// 
		//플레이어의 y좌표 빼기 박스의 y좌표 
		//플레이어의 트랜스폼이 계속 플레이어의 가운데를 가르킨다면 맞는식
		float scale = fabs(playerCd->GetSize().y * 100 / 2.0f);

		if (len < scale && playerRb->GetVelocity().y > 0)
		{
			auto playerPosition = playerTr->GetPosition();
			playerPosition.y -= scale - len;

			playerTr->SetPosition(playerPosition);
		}

		if(playerRb->GetVelocity().y > 0)
			playerRb->SetGround(true);
		else
			playerRb->SetGround(false);
	}
}

void BlockScript::OnCollisionStay(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == enums::LayerType::playerLowerBody)
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto cd = GetOwner()->GetComponent<BoxCollider2D>();

		auto playerRb = other->GetOwner()->GetComponent<RigidBody>();
		auto playerTr = other->GetOwner()->GetComponent<Transform>();
		auto playerCd = other->GetOwner()->GetComponent<BoxCollider2D>();

		float len = fabs(playerTr->GetPosition().y - tr->GetPosition().y);
		float scale = fabs(playerCd->GetSize().y * 100 / 2.0f);

		if (len < scale && playerRb->GetVelocity().y > 0)
		{
			auto playerPosition = playerTr->GetPosition();
			playerPosition.y -= scale - len - 1.0f;

			playerTr->SetPosition(playerPosition);
		}

		if (playerRb->GetVelocity().y > 0)
			playerRb->SetGround(true);
		else
			playerRb->SetGround(false);
	}
}

void BlockScript::OnCollisionExit(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == enums::LayerType::playerLowerBody)
	{
		auto rb = other->GetOwner()->GetComponent<RigidBody>();
		auto tr = other->GetOwner()->GetComponent<Transform>();

		rb->SetGround(false);
	}
}
