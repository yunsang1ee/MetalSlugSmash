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
		//	sr->SetTexture(Resources::Find<graphics::Texture>(L"Stage1초반배경"));
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
		//Player하체
		{
			playerLowerBody = object::Instantiate<Player>(LayerType::PlayerLowerBody, { 0, 0 });



			auto plysc = playerLowerBody->AddComponent<PlayerLowerBodyScript>();
			

			auto cd = playerLowerBody->AddComponent<BoxCollider2D>();
			cd->SetOffset(Vector2(-50, -50));
			playerLowerBody->GetComponent<Transform>()->SetPosition(Vector2(9000, app.getScreen().y / 2.f));


			auto an = playerLowerBody->AddComponent<Animator>();
			an->CrateAnimation(L"플레이어가만하체", Resources::Find<graphics::Texture>(L"플레이어_가만"), Vector2(550, 0), Vector2(127.72f, 148),
				Vector2(-55.f, -85.f), 1, 0.5f);
			an->CrateAnimation(L"플레이어우이동하체", Resources::Find<graphics::Texture>(L"플레이어이동"), Vector2(0.0f, 140.f), Vector2(137.75f, 86)
				, Vector2(-55.f, -19.f), 12, 0.05f);
			an->CrateAnimation(L"플레이어좌이동하체", Resources::Find<graphics::Texture>(L"플레이어좌이동"), Vector2(0.0f, 140.f), Vector2(137.75f, 86)
				, Vector2(-70.f, -19.f), 12, 0.05f);
			an->CrateAnimation(L"플레이어앉음", Resources::Find<graphics::Texture>(L"플레이어앉음"), Vector2(0.0f, 0.0f), Vector2(142.5f, 152)
				, Vector2(-60.f, -109.f), 4, 0.5f);
			an->CrateAnimation(L"플레이어앉기시작", Resources::Find<graphics::Texture>(L"플레이어앉기시작"), Vector2(0.0f, 0.f), Vector2(135.3f, 152)
				, Vector2(-60.f, -109.f), 3, 0.05f);
			an->CrateAnimation(L"플레이어앉기중간", Resources::Find<graphics::Texture>(L"플레이어앉기중간"), Vector2(0.0f, 0.f), Vector2(139.5f, 152)
				, Vector2(-60.f, -109.f), 4, 0.05f);

			an->GetCompleteEvent(L"플레이어앉기시작") = std::bind(&PlayerLowerBodyScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉기중간") = std::bind(&PlayerLowerBodyScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉음") = std::bind(&PlayerLowerBodyScript::NextAnimation, plysc);

			an->PlayAnimation(L"플레이어가만하체", true);
			//an->PlayAnimation(L"플레이어우이동하체", true);
			//an->PlayAnimation(L"플레이어앉기중간", true);
			auto rb = playerLowerBody->AddComponent<RigidBody>();

			ys::object::DontDestroyOnLoad(playerLowerBody);
		}
		//Player
		{
			player = object::Instantiate<Player>(LayerType::PlayerTop, { 0, 0 });
			auto plysc = player->AddComponent<PlayerScript>();
			
			plysc->SetLowerBody(playerLowerBody);
			


			auto texture = Resources::Find<graphics::Texture>(L"플레이어이동");
			
			auto an = player->AddComponent<Animator>();
			an->CrateAnimation(L"플레이어가만기본", Resources::Find<graphics::Texture>(L"플레이어_가만"), Vector2(10, 0), Vector2(127.72f, 148),
				Vector2(-50.f, -100.f), 4, 0.5f);
			an->CrateAnimation(L"플레이어우이동상체", texture, Vector2(0.0f, 0.0f), Vector2(137.75f, 113.0f)
				, Vector2(-50.f,-80.f), 12, 0.05f);
			an->CrateAnimation(L"플레이어좌이동상체", Resources::Find<graphics::Texture>(L"플레이어좌이동"), Vector2(0.0f, 0.0f), Vector2(137.75f, 146.0f)
				, Vector2(-70.0f, -80.f), 12, 0.05f);//약간의 부자연스러움이 있음
			an->CrateAnimation(L"플레이어기본총위상체", Resources::Find<graphics::Texture>(L"플레이어기본총위"), Vector2(0.0f, 0.0f), Vector2(123.5f, 149.0f)
				, Vector2(-55.f, -120.0f), 4, 0.5f);
			an->CrateAnimation(L"플레이어가만안보임", Resources::Find<graphics::Texture>(L"플레이어_가만"), Vector2(800, 0), Vector2(127.72f, 148),
				Vector2(-50.f, -100.f), 1, 1.f);
			

			an->PlayAnimation(L"플레이어가만기본", true);
			//an->PlayAnimation(L"플레이어가만기본총위상체", true);
			/*an->CrateAnimation(L"플레이어가만하체", Resources::Find<graphics::Texture>(L"플레이어_가만"), Vector2(550, 0), Vector2(127.72f, 148),
				Vector2(-55.f, -65.f), 1, 0.5f);
			an->PlayAnimation(L"플레이어가만하체", true);*/
		}
		
		//Enemy
		/*{
			auto enemy = object::Instantiate<Player>(LayerType::Enemy, { app.getScreenf().x, app.getScreen().y * 4 / 10.0f });

			auto sr = enemy->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어가만"));

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
		//이게 맞는지?
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
