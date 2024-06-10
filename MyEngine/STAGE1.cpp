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
#include "SoundScript.h"

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
	
		{
			auto stone = object::Instantiate<GameObject>(LayerType::Impediments, Vector2(1542, 500));

			auto sr = stone->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"돌"));

			auto bs = stone->AddComponent<BackGroundScript>();
			bs->SetParallax(0);
		}
		{
			background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, -450));

			auto sr = background->AddComponent<SpriteRenderer>();
			
			sr->SetTexture(Resources::Find<graphics::Texture>(L"Stage1"));
			
			auto bs = background->AddComponent<BackGroundScript>();
			bs->SetParallax(0);
		}
		{
			auto background = object::Instantiate<GameObject>(LayerType::BackBackGround, Vector2(9000, -250));

			auto sr = background->AddComponent<SpriteRenderer>();

			sr->SetTexture(Resources::Find<graphics::Texture>(L"뒷배경숲"));
			
			auto bs = background->AddComponent<BackGroundScript>();
			bs->SetParallax(0);
		}
		
		//Player하체
		{
			playerLowerBody = object::Instantiate<Player>(LayerType::PlayerLowerBody, { 0, 0 });


			auto an = playerLowerBody->AddComponent<Animator>();
			auto plysc = playerLowerBody->AddComponent<PlayerLowerBodyScript>();
			
			

			auto cd = playerLowerBody->AddComponent<BoxCollider2D>();
			cd->SetOffset(Vector2(-50, -50));
			playerLowerBody->GetComponent<Transform>()->SetPosition(Vector2(10000, app.getScreen().y / 2.f));


			
			an->CrateAnimation(L"플레이어위우하체", Resources::Find<graphics::Texture>(L"플레이어위_우_하체")
				, Vector2(0, 0), Vector2(125.f, 155), Vector2(-55.f, -85.f), 4, 0.1f);
			an->CrateAnimation(L"플레이어위좌하체", Resources::Find<graphics::Texture>(L"플레이어위_좌_하체")
				, Vector2(550, 0), Vector2(125.f, 155), Vector2(-55.f, -85.f), 4, 0.1f,true);

			an->CrateAnimation(L"플레이어가만하체", Resources::Find<graphics::Texture>(L"플레이어_가만")
				, Vector2(550, 0), Vector2(127.72f, 148), Vector2(-55.f, -85.f), 1, 0.1f);
			an->CrateAnimation(L"플레이어가만하체좌", Resources::Find<graphics::Texture>(L"플레이어_좌가만")
				, Vector2(550, 0), Vector2(127.72f, 148), Vector2(-55.f, -85.f), 1, 0.1f,true);

			an->CrateAnimation(L"플레이어우이동하체", Resources::Find<graphics::Texture>(L"플레이어이동")
				, Vector2(0.0f, 140.f), Vector2(137.75f, 86), Vector2(-55.f, -19.f), 12, 0.1f);
			an->CrateAnimation(L"플레이어좌이동하체", Resources::Find<graphics::Texture>(L"플레이어좌이동")
				, Vector2(0.0f, 140.f), Vector2(137.75f, 86), Vector2(-70.f, -19.f), 12, 0.1f, true);
			

			an->CrateAnimation(L"플레이어앉기시작", Resources::Find<graphics::Texture>(L"플레이어앉기시작")
				, Vector2(0.0f, 0.f), Vector2(135.3f, 152), Vector2(-60.f, -109.f), 3, 0.05f);
			an->CrateAnimation(L"플레이어앉기시작좌", Resources::Find<graphics::Texture>(L"플레이어앉기시작좌")
				, Vector2(0.0f, 0.f), Vector2(135.3f, 152), Vector2(-60.f, -109.f), 3, 0.05f,true);

			an->CrateAnimation(L"플레이어앉기중간", Resources::Find<graphics::Texture>(L"플레이어앉기중간")
				, Vector2(0.0f, 0.f), Vector2(139.5f, 152), Vector2(-60.f, -109.f), 4, 0.05f);
			an->CrateAnimation(L"플레이어앉기중간좌", Resources::Find<graphics::Texture>(L"플레이어앉기중간좌")
				, Vector2(0.0f, 0.f), Vector2(139.5f, 152), Vector2(-60.f, -109.f), 4, 0.05f,true);

			an->CrateAnimation(L"플레이어앉음", Resources::Find<graphics::Texture>(L"플레이어앉음")
				, Vector2(0.0f, 0.0f), Vector2(142.5f, 152), Vector2(-60.f, -109.f), 4, 0.5f);
			an->CrateAnimation(L"플레이어앉음좌", Resources::Find<graphics::Texture>(L"플레이어앉음좌")
				, Vector2(0.0f, 0.0f), Vector2(142.5f, 152), Vector2(-60.f, -109.f), 4, 0.5f,true);


			an->CrateAnimation(L"플레이어_앉음_공격", Resources::Find<graphics::Texture>(L"플레이어_앉음_공격")
				, Vector2(0.0f, 0.0f)
				, Vector2(212.f, 125.0f)
				, Vector2(-50, -60), 10, 0.05f);
			an->CrateAnimation(L"플레이어_앉음_공격좌", Resources::Find<graphics::Texture>(L"플레이어_앉음_공격좌")
				, Vector2(0.0f, 0.0f)
				, Vector2(211.f, 125.0f)
				, Vector2(-150, -60), 10, 0.05f,true);
			an->CrateAnimation(L"플레이어_앉음_수류탄", Resources::Find<graphics::Texture>(L"플레이어_앉음_수류탄")
				, Vector2(0.0f, 0.0f)
				, Vector2(163.0f, 112.0f)
				, Vector2(-100, -60), 6, 0.05f);
			an->CrateAnimation(L"플레이어_앉음_수류탄좌", Resources::Find<graphics::Texture>(L"플레이어_앉음_수류탄좌")
				, Vector2(0.0f, 0.0f)
				, Vector2(163.0f, 112.0f)
				, Vector2(-100, -60), 6, 0.05f,true);

			an->CrateAnimation(L"플레이어_앉음_이동", Resources::Find<graphics::Texture>(L"플레이어_앉음_이동")
				, Vector2(0.0f, 0.0f)
				, Vector2(144.0f, 97.f)
				, Vector2(-60, -40), 6, 0.05f);
			an->CrateAnimation(L"플레이어_앉음_이동좌", Resources::Find<graphics::Texture>(L"플레이어_앉음_이동좌")
				, Vector2(0.0f, 0.0f)
				, Vector2(144.0f, 97.f)
				, Vector2(-80, -40), 6, 0.05f, true);
			


			an->CrateAnimation(L"플레이어_슬라이딩", Resources::Find<graphics::Texture>(L"플레이어_슬라이딩")
				, Vector2(0.0f, 0.0f)
				, Vector2(168.f, 134.f)
				, Vector2(-50, -70), 5, 0.05f);
			an->CrateAnimation(L"플레이어_슬라이딩좌", Resources::Find<graphics::Texture>(L"플레이어_슬라이딩좌")
				, Vector2(0.0f, 0.0f)
				, Vector2(168.f, 134.f)
				, Vector2(-120, -70), 5, 0.05f,true);

			an->CrateAnimation(L"플레이어_슬라이딩_끝", Resources::Find<graphics::Texture>(L"플레이어_슬라이딩_끝")
				, Vector2(672.f, 0.0f)
				, Vector2(168.f, 134.f)
				, Vector2(-120, -70), 1, 0.05f);
			an->CrateAnimation(L"플레이어_슬라이딩좌_끝", Resources::Find<graphics::Texture>(L"플레이어_슬라이딩좌_끝")
				, Vector2(672.f, 0.0f)
				, Vector2(168.f, 134.f)
				, Vector2(-120, -70), 1, 0.05f, true);


			an->CrateAnimation(L"플레이어_슬라이딩_기본총_공격", Resources::Find<graphics::Texture>(L"플레이어_슬라이딩_기본총_공격")
				, Vector2(0.0f, 0.0f)
				, Vector2(200.f, 119.f)
				, Vector2(-50, -50), 5, 0.05f);
			an->CrateAnimation(L"플레이어_슬라이딩_기본총_공격좌", Resources::Find<graphics::Texture>(L"플레이어_슬라이딩_기본총_공격좌")
				, Vector2(0.0f, 0.0f)
				, Vector2(200.f, 119.f)
				, Vector2(-150, -50), 5, 0.05f, true);


			an->CrateAnimation(L"플레이어_점프_하체", Resources::Find<graphics::Texture>(L"플레이어_점프_하체")
				, Vector2(0.0f, 124.5f)
				, Vector2(123.f, 124.5f)
				, Vector2(-70, -70), 6, 0.1f);
			an->CrateAnimation(L"플레이어_점프_하체좌", Resources::Find<graphics::Texture>(L"플레이어_점프_하체좌")
				, Vector2(0.0f, 124.5f)
				, Vector2(123.f, 124.5f)
				, Vector2(-60, -70), 6, 0.1f,true);

			an->CrateAnimation(L"플레이어_이동_점프_하체", Resources::Find<graphics::Texture>(L"플레이어_이동_점프_하체")
				, Vector2(750.0f, 147.5f)
				, Vector2(130.f, 102.5f)
				, Vector2(-60, -38), 6, 0.1f);
			an->CrateAnimation(L"플레이어_이동_점프_하체좌", Resources::Find<graphics::Texture>(L"플레이어_이동_점프_하체좌")
				, Vector2(750.0f, 147.5f)
				, Vector2(130.f, 102.5f)
				, Vector2(-70, -38), 6, 0.1f,true);





			an->GetCompleteEvent(L"플레이어앉기시작") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉기시작좌") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉기중간") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉기중간좌") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉음") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉음좌") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);


			an->GetCompleteEvent(L"플레이어_앉음_공격") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어_앉음_공격좌") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			

			an->PlayAnimation(L"플레이어위우하체", false);
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
			


			
			
			auto an = player->AddComponent<Animator>();
			an->CrateAnimation(L"플레이어가만기본", Resources::Find<graphics::Texture>(L"플레이어_가만")
				, Vector2(10, 0)
				, Vector2(127.72f, 148)
				, Vector2(-50.f, -100.f), 4, 0.1f);
			an->CrateAnimation(L"플레이어가만기본좌", Resources::Find<graphics::Texture>(L"플레이어_좌가만")
				, Vector2(10, 0)
				, Vector2(127.72f, 148)
				, Vector2(-83.f, -100.f), 4, 0.1f, true);
			an->CrateAnimation(L"플레이어우이동상체", Resources::Find<graphics::Texture>(L"플레이어이동")
				, Vector2(0.0f, 0.0f)
				, Vector2(137.75f, 113.0f)
				, Vector2(-50.f,-80.f), 12, 0.1f);
			an->CrateAnimation(L"플레이어좌이동상체", Resources::Find<graphics::Texture>(L"플레이어좌이동")
				, Vector2(0.0f, 0.0f)
				, Vector2(137.75f, 146.0f)
				, Vector2(-70.0f, -80.f), 12, 0.1f, true); //약간의 부자연스러움이 있음
			an->CrateAnimation(L"플레이어기본총위상체", Resources::Find<graphics::Texture>(L"플레이어기본총위")
				, Vector2(0.0f, 0.0f)
				, Vector2(123.5f, 149.0f)
				, Vector2(-45.f, -120.0f), 4, 0.1f);
			an->CrateAnimation(L"플레이어기본총위상체좌", Resources::Find<graphics::Texture>(L"플레이어기본총위좌")
				, Vector2(0.0f, 0.0f)
				, Vector2(123.5f, 149.0f)
				, Vector2(-65.f, -120.0f), 4, 0.1f, true);
			an->CrateAnimation(L"플레이어가만안보임", Resources::Find<graphics::Texture>(L"플레이어_가만")
				, Vector2(800, 0)
				, Vector2(127.72f, 148)
				, Vector2(-50.f, -100.f), 1, 1.f);
			



			an->CrateAnimation(L"플레이어_기본총_우공격_화염", Resources::Find<graphics::Texture>(L"플레이어_기본총_우공격")
				, Vector2(0, 0)
				, Vector2(200, 110)
				, Vector2(-50.f, -75.f), 3, 0.05f);
			an->CrateAnimation(L"플레이어_기본총_우공격", Resources::Find<graphics::Texture>(L"플레이어_기본총_우공격")
				, Vector2(600, 0)
				, Vector2(145.5f, 110)
				, Vector2(-50.f, -100.f), 7, 0.05f);
			an->CrateAnimation(L"플레이어_기본총_우공격_점프_화염", Resources::Find<graphics::Texture>(L"플레이어_기본총_우공격")
				, Vector2(1620, 0)
				, Vector2(200, 110.f)
				, Vector2(-50.f, -80.f), 3, 0.05f);
			an->CrateAnimation(L"플레이어_기본총_우공격_점프", Resources::Find<graphics::Texture>(L"플레이어_기본총_우공격")
				, Vector2(2210, 0)
				, Vector2(144.9f, 110.f)
				, Vector2(-50.f, -80.f), 7, 0.05f);


			an->CrateAnimation(L"플레이어_기본총_좌공격_화염", Resources::Find<graphics::Texture>(L"플레이어_기본총_좌공격")
				, Vector2(0, 0)
				, Vector2(200, 110)
				, Vector2(-50.f, -75.f), 3, 0.05f, true);
			an->CrateAnimation(L"플레이어_기본총_좌공격", Resources::Find<graphics::Texture>(L"플레이어_기본총_좌공격")
				, Vector2(600, 0)
				, Vector2(145.5f, 110)
				, Vector2(-50.f, -100.f), 7, 0.05f, true);
			an->CrateAnimation(L"플레이어_기본총_좌공격_점프_화염", Resources::Find<graphics::Texture>(L"플레이어_기본총_좌공격")
				, Vector2(1620, 0)
				, Vector2(200, 110.f)
				, Vector2(-140.f, -80.f), 3, 0.05f, true);
			an->CrateAnimation(L"플레이어_기본총_좌공격_점프", Resources::Find<graphics::Texture>(L"플레이어_기본총_좌공격")
				, Vector2(2210, 0)
				, Vector2(144.9f, 110.f)
				, Vector2(-50.f, -80.f), 7, 0.05f, true);

			an->GetCompleteEvent(L"플레이어_기본총_우공격_화염") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"플레이어_기본총_우공격") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"플레이어_기본총_우공격_점프_화염") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"플레이어_기본총_우공격_점프") = std::bind(&PlayerScript::NextAnimation, plysc);

			an->GetCompleteEvent(L"플레이어_기본총_좌공격_화염") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"플레이어_기본총_좌공격") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"플레이어_기본총_좌공격_점프_화염") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"플레이어_기본총_좌공격_점프") = std::bind(&PlayerScript::NextAnimation, plysc);

			an->PlayAnimation(L"플레이어_기본총_좌공격_화염", true);
			
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
		
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 10, 10 });
			auto block = Blocks[Blocks.size() - 1];
			
			block->AddComponent<BoxCollider2D>();
			block->GetComponent<BoxCollider2D>()->setName(L"BackGround");
			block->GetComponent<BoxCollider2D>()->SetSize(Vector2(0.1f, 30.f));
			block->AddComponent<BlockScript>();
		
		}
		
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

			bx->setName(L"BackGrounds");
			bx->SetSize(Vector2(3.64f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 9715, 280 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"BackGrounds");
			bx->SetSize(Vector2(1.83f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 10140, 480 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"BackGrounds");
			bx->SetSize(Vector2(3.66f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 11013, 630 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"BackGrounds");
			bx->SetSize(Vector2(1.42f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 11083, 454 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"BackGrounds");
			bx->SetSize(Vector2(1.47f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 10786, 270 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"BackGrounds");
			bx->SetSize(Vector2(6.25f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 10572, 310 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"BackGrounds");
			bx->SetSize(Vector2(1.77f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 11564, 457 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"BackGrounds");
			bx->SetSize(Vector2(4.12f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 12129, 280 });
			auto block = Blocks[Blocks.size() - 1];
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"BackGrounds");
			bx->SetSize(Vector2(2.08f, 0.23f));
			block->AddComponent<BlockScript>();
		}
		


	
		//플레이어보다 앞에있는 배경
		{
			auto frontBackground = object::Instantiate<GameObject>(LayerType::FrontGround, { 5576, 691 });
			auto sr = frontBackground->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"잠수함구조물1"));
		}
		{
			auto frontBackground = object::Instantiate<GameObject>(LayerType::FrontGround, { 6050, 450 });
			auto sr = frontBackground->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"잠수함구조물2"));
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
		{
			auto sound = object::Instantiate<GameObject>(LayerType::BackGround, { 0,0 });
			auto sd = sound->AddComponent<SoundScript>();
			sd->soundLoad(L"..\\Resource\\sd.mp3");
			sd->playSound(L"..\\Resource\\sd.mp3");
		}
		Scene::Init();
	}

	void ys::STAGE1::Update()
	{
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
