#include "BlockScript.h"
#include<ysGameObject.h>
#include<ysBoxCollider2D.h>
#include<ysSceneManager.h>
#include<ysScene.h>
#include<ysObject.h>
#include <ysRigidBody.h>
#include <ysTransform.h>
#include <ysCircleCollider2D.h>
#include <ysInputManager.h>
#include "drawBoxScript.h"
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
	switch (other->GetOwner()->GetLayerType())
	{
	case ys::enums::LayerType::Projectile:
	{
		if (other->GetColliderType() == ColliderType::Circle2D)
			break;
		else
			__fallthrough;
	}
	case ys::enums::LayerType::PlayerLowerBody:
	{
		auto tr = GetOwner()->GetComponent<Transform>();

		auto otherRb = other->GetOwner()->GetComponent<RigidBody>();
		auto otherTr = other->GetOwner()->GetComponent<Transform>();
		auto otherCd = other->GetOwner()->GetComponent<BoxCollider2D>();

		float len = fabs(otherTr->GetPosition().y - tr->GetPosition().y);
		float scale = fabs(otherCd->GetSize().y * 100 / 2.0f);

		if (len < scale && otherRb->GetVelocity().y > 0)
		{
			auto otherPosition = otherTr->GetPosition();
			otherPosition.y -= scale - len;

			otherTr->SetPosition(otherPosition);
		}

		if (otherRb->GetVelocity().y > 0)
			otherRb->SetGround(true);
		else
			otherRb->SetGround(false);
		break;
	}
	default:
		break;
	}

}

void BlockScript::OnCollisionStay(Collider* other)
{
	switch (other->GetOwner()->GetLayerType())
	{
	case ys::enums::LayerType::Projectile:
	{
		if (other->GetColliderType() == ColliderType::Circle2D)
			break;
		else
			__fallthrough;
	}
	case ys::enums::LayerType::PlayerLowerBody:
	{
		auto tr = GetOwner()->GetComponent<Transform>();

		auto otherRb = other->GetOwner()->GetComponent<RigidBody>();
		auto otherTr = other->GetOwner()->GetComponent<Transform>();
		auto otherCd = other->GetOwner()->GetComponent<BoxCollider2D>();

		float len = fabs(otherTr->GetPosition().y - tr->GetPosition().y);
		float scale = fabs(otherCd->GetSize().y * 100 / 2.0f);

		if (len < scale && otherRb->GetVelocity().y > 0)
		{
			auto otherPosition = otherTr->GetPosition();
			otherPosition.y -= scale - len - 1.0f;

			otherTr->SetPosition(otherPosition);
		}

		if (otherRb->GetVelocity().y > 0)
			otherRb->SetGround(true);
		else
			otherRb->SetGround(false);
		break;
	}
	case ys::enums::LayerType::Tool:
	{
		if (ys::InputManager::getKeyDown(VK_RBUTTON) && ys::InputManager::getKey(VK_CONTROL))
			ys::object::Destroy(GetOwner());
		break;
	}
	default:
		break;
	}
}

void BlockScript::OnCollisionExit(Collider* other)
{
	switch (other->GetOwner()->GetLayerType())
	{
	case ys::enums::LayerType::Projectile:
	{
		if (other->GetColliderType() == ColliderType::Circle2D)
			break;
		else
			__fallthrough;
	}
	case ys::enums::LayerType::PlayerLowerBody:
	{
		auto rb = other->GetOwner()->GetComponent<RigidBody>();
		auto tr = other->GetOwner()->GetComponent<Transform>();

		rb->SetGround(false);
		break;
	}
	case ys::enums::LayerType::Tool:
	{
		if (ys::InputManager::getKeyDown(VK_RBUTTON) && ys::InputManager::getKey(VK_CONTROL))
			ys::object::Destroy(GetOwner());
		break;
	}
	default:
		break;
	}
}
