#include<fstream>
#include "WallScript.h"
#include "YSapplication.h"
#include "ysRenderer.h"
#include "ysTransform.h"
#include "BlockScript.h"
#include "ysGameObject.h"
#include "ysBoxCollider2D.h"
#include "ysSceneManager.h"
#include "ysInputManager.h"
#include "ysObject.h"
#include <ysRigidBody.h>
extern ys::Application app;
WallScript::WallScript()
{
}

WallScript::~WallScript()
{
}

void WallScript::Init()
{
}

void WallScript::Update()
{
	
	
	
}

void WallScript::LateUpdate()
{
}

void WallScript::Render(HDC hDC)
{
}

void WallScript::Destroy()
{
}

void WallScript::OnCollisionEnter(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == enums::LayerType::PlayerLowerBody)
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto cd = GetOwner()->GetComponent<BoxCollider2D>();

		auto playerRb = other->GetOwner()->GetComponent<RigidBody>();
		auto playerTr = other->GetOwner()->GetComponent<Transform>();
		auto playerCd = other->GetOwner()->GetComponent<BoxCollider2D>();

		
		float scale = fabs(playerCd->GetSize().x * 100 / 2.0f);

		

		if (playerTr->GetPosition().x - scale < tr->GetPosition().x + cd->GetSize().x * 100 
			&& playerTr->GetPosition().x > tr->GetPosition().x + cd->GetSize().x * 100 )
		{
			auto playerPosition = playerTr->GetPosition();
			auto len = fabs((playerTr->GetPosition().x - scale) - (tr->GetPosition().x + cd->GetSize().x * 100));
			playerPosition.x += len;
				
				

			playerTr->SetPosition(playerPosition);
		}
		else if (playerTr->GetPosition().x + scale > tr->GetPosition().x 
			&& playerTr->GetPosition().x < tr->GetPosition().x)
		{
			auto playerPosition = playerTr->GetPosition();
			auto len = fabs((playerTr->GetPosition().x + scale) - (tr->GetPosition().x));
			playerPosition.x -= len;

			playerTr->SetPosition(playerPosition);
		}
	}
}

void WallScript::OnCollisionStay(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == enums::LayerType::PlayerLowerBody)
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto cd = GetOwner()->GetComponent<BoxCollider2D>();

		auto playerRb = other->GetOwner()->GetComponent<RigidBody>();
		auto playerTr = other->GetOwner()->GetComponent<Transform>();
		auto playerCd = other->GetOwner()->GetComponent<BoxCollider2D>();


		float scale = fabs(playerCd->GetSize().x * 100 / 2.0f);



		if (playerTr->GetPosition().x - scale < tr->GetPosition().x + cd->GetSize().x * 100
			&& playerTr->GetPosition().x > tr->GetPosition().x + cd->GetSize().x * 100)
		{
			auto playerPosition = playerTr->GetPosition();
			auto len = fabs((playerTr->GetPosition().x - scale) - (tr->GetPosition().x + cd->GetSize().x * 100));
			playerPosition.x += len;



			playerTr->SetPosition(playerPosition);
		}
		else if (playerTr->GetPosition().x + scale > tr->GetPosition().x
			&& playerTr->GetPosition().x < tr->GetPosition().x)
		{
			auto playerPosition = playerTr->GetPosition();
			auto len = fabs((playerTr->GetPosition().x + scale) - (tr->GetPosition().x));
			playerPosition.x -= len;

			playerTr->SetPosition(playerPosition);
		}
	}
}

void WallScript::OnCollisionExit(Collider* other)
{
	
}
