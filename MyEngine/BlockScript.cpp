#include "BlockScript.h"
#include<ysGameObject.h>
#include<ysBoxCollider2D.h>
#include<ysSceneManager.h>
#include<ysScene.h>
#include <ysRigidBody.h>
#include <ysTransform.h>
#include <ysCircleCollider2D.h>
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
	auto scene = dynamic_cast<Scene*>(SceneManager::GetActiveScene());
	auto plyr = scene->GetLayer(LayerType::Player)->GetGameObjects()[0];
}

void BlockScript::LateUpdate()
{
}

void BlockScript::Render(HDC hDC)
{
}

void BlockScript::OnCollisionEnter(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == enums::LayerType::Player)
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

		if(playerRb->GetVelocity().y > 0)
			playerRb->SetGround(true);
		else
			playerRb->SetGround(false);
	}
}

void BlockScript::OnCollisionStay(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == enums::LayerType::Player)
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
	if (other->GetOwner()->GetLayerType() == enums::LayerType::Player)
	{
		auto rb = other->GetOwner()->GetComponent<RigidBody>();
		auto tr = other->GetOwner()->GetComponent<Transform>();

		rb->SetGround(false);
	}
}
