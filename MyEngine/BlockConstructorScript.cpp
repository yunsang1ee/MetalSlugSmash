#include "BlockConstructorScript.h"
#include "BlockScript.h"
#include <ysObject.h>
#include <ysSpriteRenderer.h>
#include <ysResources.h>
#include <ysBoxCollider2D.h>
#include <ysRigidBody.h>
#include <YSapplication.h>

extern ys::Application app;
namespace ys
{
	BlockConstructorScript::BlockConstructorScript()
	{
	}
	BlockConstructorScript::~BlockConstructorScript()
	{
	}
	void BlockConstructorScript::Init()
	{
		for(int i = 0; i < 5; ++i)
		{
			auto position = Vector2(app.getScreenf().x + (i * 324.0f), 761.5f);
			auto block = object::Instantiate<GameObject>(LayerType::Block, position);
			auto sr = block->AddComponent<SpriteRenderer>();
			auto texture = Resources::Find<graphics::Texture>(L"보스발판");
			sr->SetTexture(texture);
			sr->SetOffset(Vector2(153.0f, 800.0f), Vector2(6227.0f, 0.0f));
			sr->SetSizeByScreen(Vector2(326.0f, 185.0f));
			auto bx = block->AddComponent<BoxCollider2D>();
			bx->SetOffset(Vector2::Down * 20.0f);
			bx->SetSize(Vector2(3.26f, 1.85f));
			block->AddComponent<BlockScript>()->SetOffset(Vector2::Down * 20.0f);
			auto rb = block->AddComponent<RigidBody>();
			rb->SetFriction(0.0f);
			rb->SetGravity(Vector2::Zero);
			rb->SetVelocity(Vector2::Left * 100.0f);
			blocks.push_back(block);
		}
	}
	void BlockConstructorScript::Update()
	{
		for(auto block : blocks)
		{
			auto tr = block->GetComponent<Transform>();
			if (tr->GetPosition().x < -326.0f)
			{
				tr->SetPosition(Vector2(1296.0f, tr->GetPosition().y));
			}
		}
	}
	void BlockConstructorScript::LateUpdate()
	{
	}
	void BlockConstructorScript::Render(HDC hDC)
	{
	}
	void BlockConstructorScript::OnCollisionEnter(Collider* other)
	{
	}
	void BlockConstructorScript::OnCollisionStay(Collider* other)
	{
	}
	void BlockConstructorScript::OnCollisionExit(Collider* other)
	{
	}
}
