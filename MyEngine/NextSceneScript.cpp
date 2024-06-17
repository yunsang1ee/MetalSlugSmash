#include "NextSceneScript.h"
#include "ysGameObject.h"
#include "ysCollider.h"
#include "ysObject.h"
#include "ysResources.h"
#include "YSapplication.h"
#include <ysSpriteRenderer.h>
#include <ysRenderer.h>
#include <ysRigidBody.h>

extern ys::Application app;
ys::NextSceneScript::NextSceneScript() : isNext(false), start(nullptr)
{
}

ys::NextSceneScript::~NextSceneScript()
{
}

void ys::NextSceneScript::Init()
{
}

void ys::NextSceneScript::Update()
{
	if (GetOwner()->GetLayerType() == LayerType::FrontGround)
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto sr = GetOwner()->GetComponent<SpriteRenderer>();

		if (tr->GetPosition().x < renderer::mainCamera->GetLookPosition().x - app.getScreenf().x && !isNext)
		{
			auto rb = GetOwner()->AddComponent<RigidBody>();
			rb->SetVelocity(Vector2::Zero);
			if(SceneManager::GetActiveScene()->getName() == L"Stage1")
				SceneManager::LoadScene(L"BossScene");
			isNext = true;
			rb->SetVelocity(Vector2::Left * 1200.0f);
		}
		int width = sr->GetTexture()->GetWidth();

		if (tr->GetPosition().x < renderer::mainCamera->GetLookPosition().x - app.getScreenf().x - width)
		{
			object::Destroy(GetOwner());
		}
	}
}

void ys::NextSceneScript::LateUpdate()
{
}

void ys::NextSceneScript::Render(HDC hDC)
{
}

void ys::NextSceneScript::OnCollisionEnter(Collider* other)
{
	if (other->GetOwner()->GetLayerType() == LayerType::PlayerLowerBody && !start)
	{
		start = object::Instantiate<GameObject>(LayerType::FrontGround
			, Vector2(renderer::mainCamera->GetLookPosition().x + app.getScreenf().x / 2.0f, -50.0f));

		start->AddComponent<NextSceneScript>();
		auto sr = start->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"¾ÀÀüÈ¯"));
		auto rb = start->AddComponent<RigidBody>();
		rb->SetGravity(Vector2::Zero);
		rb->SetFriction(0.0f);
		rb->SetVelocity(Vector2::Left * 1200.0f);
		object::DontDestroyOnLoad(start);
	}
}

void ys::NextSceneScript::OnCollisionStay(Collider* other)
{
}

void ys::NextSceneScript::OnCollisionExit(Collider* other)
{
}
