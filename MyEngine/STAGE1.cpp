#include "STAGE1.h"
#include <random>
#include <ysTransform.h>
#include <ysSpriteRenderer.h>
#include "ysTitleScene.h"
#include "ysInputManager.h"
#include "ysSceneManager.h"
#include "ysObject.h"
#include "ysResources.h"
#include "YSapplication.h"
#include "ysTexture.h"
#include "ysPlayerScript.h"
#include "ysBackGroundScript.h"
#include "ysCamera.h"
#include "ysRenderer.h"
#include "BulletScript.h"
#include <ysBoxCollider2D.h>
#include <ysCollisionManager.h>
#include "ysEnemyScript.h"
#include"ysPlayer.h"
#include "CameraScript.h"
#include "BlockScript.h"
#include"drawBoxScript.h"
#include"ysAnimation.h"
#include"ysAnimator.h"
#include "PlayerLowerBodyScript.h"
#include <ysRigidBody.h>

extern ys::Application app;
namespace ys {
	ys::STAGE1::STAGE1()
	{
	}

	ys::STAGE1::~STAGE1()
	{
	}
	void ys::STAGE1::Init()
	{
		CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(LayerType::Enemy, LayerType::Projectile, true);
		CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::Block, true);
		CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::BackGround, true);
		//backGrounds
		//{
		//	backBackground = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, -92));

		//	auto sr = backBackground->AddComponent<SpriteRenderer>();
		//	sr->SetTexture(Resources::Find<graphics::Texture>(L"Stage1�ʹݹ��"));
		//	//sr->SetSizeByScreen(Vector2(sr->GetTexture()->GetWidth() , sr->GetTexture()->GetHeight() ));

		//	auto bs = backBackground->AddComponent<BackGroundScript>();
		//	bs->SetParallax(-100);
		//}
		{
			background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, -450));

			auto sr = background->AddComponent<SpriteRenderer>();
			
			sr->SetTexture(Resources::Find<graphics::Texture>(L"Stage1"));
			//background->AddComponent<Transform>();
			auto bs = background->AddComponent<BackGroundScript>();
			bs->SetParallax(0);
		}
		//Player��ü
		{
			playerLowerBody = object::Instantiate<Player>(LayerType::PlayerLowerBody, { 0, 0 });



			auto plysc = playerLowerBody->AddComponent<PlayerLowerBodyScript>();
			

			auto cd = playerLowerBody->AddComponent<BoxCollider2D>();
			cd->SetOffset(Vector2(-50, -50));
			playerLowerBody->GetComponent<Transform>()->SetPosition(Vector2(9000, app.getScreen().y / 2.f));


			auto an = playerLowerBody->AddComponent<Animator>();
			an->CrateAnimation(L"�÷��̾����ü", Resources::Find<graphics::Texture>(L"�÷��̾�_����"), Vector2(550, 0), Vector2(127.72f, 148),
				Vector2(-55.f, -85.f), 1, 0.5f);
			an->CrateAnimation(L"�÷��̾���̵���ü", Resources::Find<graphics::Texture>(L"�÷��̾��̵�"), Vector2(0.0f, 140.f), Vector2(137.75f, 86)
				, Vector2(-55.f, -19.f), 12, 0.05f);
			an->CrateAnimation(L"�÷��̾����̵���ü", Resources::Find<graphics::Texture>(L"�÷��̾����̵�"), Vector2(0.0f, 140.f), Vector2(137.75f, 86)
				, Vector2(-70.f, -19.f), 12, 0.05f);
			an->CrateAnimation(L"�÷��̾����", Resources::Find<graphics::Texture>(L"�÷��̾����"), Vector2(0.0f, 0.0f), Vector2(142.5f, 152)
				, Vector2(-60.f, -109.f), 4, 0.5f);
			an->CrateAnimation(L"�÷��̾�ɱ����", Resources::Find<graphics::Texture>(L"�÷��̾�ɱ����"), Vector2(0.0f, 0.f), Vector2(135.3f, 152)
				, Vector2(-60.f, -109.f), 3, 0.05f);
			an->CrateAnimation(L"�÷��̾�ɱ��߰�", Resources::Find<graphics::Texture>(L"�÷��̾�ɱ��߰�"), Vector2(0.0f, 0.f), Vector2(139.5f, 152)
				, Vector2(-60.f, -109.f), 4, 0.05f);

			an->GetCompleteEvent(L"�÷��̾�ɱ����") = std::bind(&PlayerLowerBodyScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�ɱ��߰�") = std::bind(&PlayerLowerBodyScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾����") = std::bind(&PlayerLowerBodyScript::NextAnimation, plysc);

			an->PlayAnimation(L"�÷��̾����ü", true);
			//an->PlayAnimation(L"�÷��̾���̵���ü", true);
			//an->PlayAnimation(L"�÷��̾�ɱ��߰�", true);
			auto rb = playerLowerBody->AddComponent<RigidBody>();

			ys::object::DontDestroyOnLoad(playerLowerBody);
		}
		//Player
		{
			player = object::Instantiate<Player>(LayerType::PlayerTop, { 0, 0 });
			auto plysc = player->AddComponent<PlayerScript>();
			
			plysc->SetLowerBody(playerLowerBody);
			


			auto texture = Resources::Find<graphics::Texture>(L"�÷��̾��̵�");
			
			auto an = player->AddComponent<Animator>();
			an->CrateAnimation(L"�÷��̾���⺻", Resources::Find<graphics::Texture>(L"�÷��̾�_����"), Vector2(10, 0), Vector2(127.72f, 148),
				Vector2(-50.f, -100.f), 4, 0.5f);
			an->CrateAnimation(L"�÷��̾���̵���ü", texture, Vector2(0.0f, 0.0f), Vector2(137.75f, 113.0f)
				, Vector2(-50.f,-80.f), 12, 0.05f);
			an->CrateAnimation(L"�÷��̾����̵���ü", Resources::Find<graphics::Texture>(L"�÷��̾����̵�"), Vector2(0.0f, 0.0f), Vector2(137.75f, 146.0f)
				, Vector2(-70.0f, -80.f), 12, 0.05f);//�ణ�� ���ڿ��������� ����
			an->CrateAnimation(L"�÷��̾�⺻������ü", Resources::Find<graphics::Texture>(L"�÷��̾�⺻����"), Vector2(0.0f, 0.0f), Vector2(123.5f, 149.0f)
				, Vector2(-55.f, -120.0f), 4, 0.5f);
			an->CrateAnimation(L"�÷��̾���Ⱥ���", Resources::Find<graphics::Texture>(L"�÷��̾�_����"), Vector2(800, 0), Vector2(127.72f, 148),
				Vector2(-50.f, -100.f), 1, 1.f);
			

			an->PlayAnimation(L"�÷��̾���⺻", true);
			//an->PlayAnimation(L"�÷��̾���⺻������ü", true);
			/*an->CrateAnimation(L"�÷��̾����ü", Resources::Find<graphics::Texture>(L"�÷��̾�_����"), Vector2(550, 0), Vector2(127.72f, 148),
				Vector2(-55.f, -65.f), 1, 0.5f);
			an->PlayAnimation(L"�÷��̾����ü", true);*/
		}
		
		//Enemy
		/*{
			auto enemy = object::Instantiate<Player>(LayerType::Enemy, { app.getScreenf().x, app.getScreen().y * 4 / 10.0f });

			auto sr = enemy->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��"));

			enemy->AddComponent<EnemyScript>();
			auto cd = enemy->AddComponent<CircleCollider2D>();
			cd->SetOffset(Vector2(20, 30));
		}*/
		//block1
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size()-1] = object::Instantiate<GameObject>(LayerType::Block, { 0, 681});
			auto block = Blocks[Blocks.size() - 1];
			
			block->AddComponent<BoxCollider2D>();
			block->GetComponent<BoxCollider2D>()->setName(L"BackGround");
			block->GetComponent<BoxCollider2D>()->SetSize(Vector2(30, 0.23f));
			block->AddComponent<BlockScript>();

		}
		//block2
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 0, app.getScreen().y-100.f});
			auto block = Blocks[Blocks.size() - 1];
			
			auto bx=block->AddComponent<BoxCollider2D>();
			bx->setName(L"BackGround");
			//tr->SetScale(Vector2(500, 0.1f));
			bx->SetSize(Vector2(500, 1.f));
			block->AddComponent<BlockScript>();
			
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 3846, 637 });
			auto block = Blocks[Blocks.size() - 1];
			
			auto bx = block->AddComponent<BoxCollider2D>();
			bx->setName(L"BackGround");
			bx->SetSize(Vector2(2.75f, 0.23f));
			block->AddComponent<BlockScript>();
		
		}
	
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 4200, 461 });
			auto block = Blocks[Blocks.size() - 1];
			
			auto bx = block->AddComponent<BoxCollider2D>();
			bx->setName(L"BackGround");
			bx->SetSize(Vector2(8.06f, 0.23f));
			block->AddComponent<BlockScript>();

		}
	
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 4993, 645 });
			auto block = Blocks[Blocks.size() - 1];
			
			auto bx = block->AddComponent<BoxCollider2D>();
			bx->setName(L"BackGround");
			bx->SetSize(Vector2(2.93f, 0.23f));
			block->AddComponent<BlockScript>();

		}
		{
	
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 5261, 460 });
			auto block = Blocks[Blocks.size() - 1];
			
			auto bx = block->AddComponent<BoxCollider2D>();
			bx->setName(L"BackGround");
			bx->SetSize(Vector2(6.35f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
		
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 6098, 459 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();
			
			bx->setName(L"BackGround");
			bx->SetSize(Vector2(7.29f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 6864, 640 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();
			
			bx->setName(L"BackGround");
			bx->SetSize(Vector2(2.93f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 9276, 488 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"BackGround");
			bx->SetSize(Vector2(3.64f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		//Camera
		{
			camera = object::Instantiate<GameObject>(LayerType::Camera);
			renderer::mainCamera = camera->AddComponent<Camera>();
			renderer::mainCamera->SetTarget(player);
			camera->GetComponent<Camera>()->SetMinMax(Vector2(650, 420), Vector2(
				15600, 363));
			camera->AddComponent<CameraScript>();
		}
		{
			auto drawBox = object::Instantiate<GameObject>(LayerType::Block, { 0, 0 });
			auto bx = drawBox->AddComponent<BoxCollider2D>();
			drawBox->AddComponent<drawBoxScript>();
		}
		Scene::Init();
	}

	void ys::STAGE1::Update()
	{
		//�̰� �´���?
		Scene::Update();
	}

	void ys::STAGE1::LateUpdate()
	{
		Scene::LateUpdate();
		
	}

	void ys::STAGE1::Render(HDC hDC, const int& index)
	{
		Scene::Render(hDC, index);
	}

	void STAGE1::Destroy()
	{
	}

	void STAGE1::OnEnter()
	{
	}
	void STAGE1::OnExit() 
	{
	}


}
