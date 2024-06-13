#include "STAGE1.h"
#include <random>
#include <fstream>
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
		CollisionManager::CollisionLayerCheck(LayerType::playerLowerBody, LayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(LayerType::playerLowerBody, LayerType::Block, true);
		CollisionManager::CollisionLayerCheck(LayerType::playerLowerBody, LayerType::BackGround, true);
		CollisionManager::CollisionLayerCheck(LayerType::Enemy, LayerType::Projectile, true);
		CollisionManager::CollisionLayerCheck(LayerType::Block, LayerType::Tool, true);
		//backGrounds
		//{
		//	backBackground = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, -92));

		//	auto sr = backBackground->AddComponent<SpriteRenderer>();
		//	sr->SetTexture(Resources::Find<graphics::Texture>(L"Stage1초반배경"));
		//	//sr->SetSizeByScreen(Vector2(sr->GetTexture()->GetWidth() , sr->GetTexture()->GetHeight() ));

	
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
			backBackground = object::Instantiate<GameObject>(LayerType::BackBackGround, Vector2(9100, -250));

			auto sr = backBackground->AddComponent<SpriteRenderer>();

			sr->SetTexture(Resources::Find<graphics::Texture>(L"뒷배경숲"));
			
			auto bs = backBackground->AddComponent<BackGroundScript>();
			bs->SetParallax(0);
		}
		//Player하체
		{
			playerLowerBody = object::Instantiate<Player>(LayerType::playerLowerBody, { 0, 0 });



			auto plysc = playerLowerBody->AddComponent<PlayerLowerBodyScript>();
			

			auto cd = playerLowerBody->AddComponent<BoxCollider2D>();
			cd->SetOffset(Vector2(-50, -50));
			playerLowerBody->GetComponent<Transform>()->SetPosition(Vector2(10000, app.getScreen().y / 2.f));


			auto an = playerLowerBody->AddComponent<Animator>();
			an->CrateAnimation(L"플레이어위우하체", Resources::Find<graphics::Texture>(L"플레이어위_우_하체")
				, Vector2(550, 0), Vector2(127.72f, 148), Vector2(-55.f, -85.f), 1, 0.1f);
			an->CrateAnimation(L"플레이어위좌하체", Resources::Find<graphics::Texture>(L"플레이어위_좌_하체")
				, Vector2(550, 0), Vector2(127.72f, 148), Vector2(-55.f, -85.f), 1, 0.1f);

			an->CrateAnimation(L"플레이어가만하체", Resources::Find<graphics::Texture>(L"플레이어_가만")
				, Vector2(550, 0), Vector2(127.72f, 148), Vector2(-55.f, -85.f), 1, 0.1f);
			an->CrateAnimation(L"플레이어가만하체좌", Resources::Find<graphics::Texture>(L"플레이어_좌가만")
				, Vector2(550, 0), Vector2(127.72f, 148), Vector2(-55.f, -85.f), 1, 0.1f);

			an->CrateAnimation(L"플레이어우이동하체", Resources::Find<graphics::Texture>(L"플레이어이동")
				, Vector2(0.0f, 140.f), Vector2(137.75f, 86), Vector2(-55.f, -19.f), 12, 0.1f);
			an->CrateAnimation(L"플레이어좌이동하체", Resources::Find<graphics::Texture>(L"플레이어좌이동")
				, Vector2(0.0f, 140.f), Vector2(137.75f, 86), Vector2(-70.f, -19.f), 12, 0.1f, true);


			an->CrateAnimation(L"플레이어앉기시작", Resources::Find<graphics::Texture>(L"플레이어앉기시작")
				, Vector2(0.0f, 0.f), Vector2(135.3f, 152), Vector2(-60.f, -109.f), 3, 0.05f);
			an->CrateAnimation(L"플레이어앉기시작좌", Resources::Find<graphics::Texture>(L"플레이어앉기시작좌")
				, Vector2(0.0f, 0.f), Vector2(135.3f, 152), Vector2(-60.f, -109.f), 3, 0.05f);

			an->CrateAnimation(L"플레이어앉기중간", Resources::Find<graphics::Texture>(L"플레이어앉기중간")
				, Vector2(0.0f, 0.f), Vector2(139.5f, 152), Vector2(-60.f, -109.f), 4, 0.05f);
			an->CrateAnimation(L"플레이어앉기중간좌", Resources::Find<graphics::Texture>(L"플레이어앉기중간좌")
				, Vector2(0.0f, 0.f), Vector2(139.5f, 152), Vector2(-60.f, -109.f), 4, 0.05f);

			an->CrateAnimation(L"플레이어앉음", Resources::Find<graphics::Texture>(L"플레이어앉음")
				, Vector2(0.0f, 0.0f), Vector2(142.5f, 152), Vector2(-60.f, -109.f), 4, 0.5f);
			an->CrateAnimation(L"플레이어앉음좌", Resources::Find<graphics::Texture>(L"플레이어앉음좌")
				, Vector2(0.0f, 0.0f), Vector2(142.5f, 152), Vector2(-60.f, -109.f), 4, 0.5f);

			an->GetCompleteEvent(L"플레이어앉기시작") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉기시작좌") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉기중간") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉기중간좌") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉음") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"플레이어앉음좌") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			

			an->PlayAnimation(L"플레이어가만하체", true);
			//an->PlayAnimation(L"플레이어우이동하체", true);
			//an->PlayAnimation(L"플레이어앉기중간", true);
			auto rb = playerLowerBody->AddComponent<RigidBody>();
			rb->SetGravity(Vector2::Down * 3.0f);
			ys::object::DontDestroyOnLoad(playerLowerBody);
		}
		//Player
		{
			player = object::Instantiate<Player>(LayerType::PlayerTop, { 0, 0 });
			auto plysc = player->AddComponent<PlayerScript>();
			
			plysc->SetLowerBody(playerLowerBody);
			
			auto an = player->AddComponent<Animator>();
			//가만
			an->CrateAnimation(L"플레이어가만기본", Resources::Find<graphics::Texture>(L"플레이어_가만")
				, Vector2(10, 0), Vector2(127.72f, 148), Vector2(-50.f, -100.f), 4, 0.1f);
			an->CrateAnimation(L"플레이어가만기본좌", Resources::Find<graphics::Texture>(L"플레이어_좌가만")
				, Vector2(10, 0), Vector2(127.72f, 148),Vector2(-83.f, -100.f), 4, 0.1f, true);

			//이동
			an->CrateAnimation(L"플레이어이동상체", Resources::Find<graphics::Texture>(L"플레이어이동")
				, Vector2(0.0f, 0.0f), Vector2(137.75f, 113.0f), Vector2(-50.f,-80.f), 12, 0.1f);
			an->CrateAnimation(L"플레이어이동상체좌", Resources::Find<graphics::Texture>(L"플레이어좌이동")
				, Vector2(0.0f, 0.0f), Vector2(137.75f, 146.0f), Vector2(-70.0f, -80.f), 12, 0.1f, true);

			//가만점프
			an->CrateAnimation(L"플레이어가만점프", Resources::Find<graphics::Texture>(L"플레이어가만점프")
				, Vector2(0.0f, 0.0f), Vector2(137.75f, 149.0f), Vector2(-60.0f, -92.0f), 6, 0.1f);
			an->CrateAnimation(L"플레이어가만점프좌", Resources::Find<graphics::Texture>(L"플레이어가만점프좌")
				, Vector2(0.0f, 0.0f), Vector2(137.75f, 149.0f), Vector2(-70.0f, -92.0f), 6, 0.1f, true);

			//이동점프
			an->CrateAnimation(L"플레이어이동점프", Resources::Find<graphics::Texture>(L"플레이어이동점프")
				, Vector2(826.5f, 0.0f), Vector2(137.75f, 149.0f), Vector2(-55.0f, -92.0f), 6, 0.1f);
			an->CrateAnimation(L"플레이어이동점프좌", Resources::Find<graphics::Texture>(L"플레이어이동점프좌")
				, Vector2(826.5f, 0.0f), Vector2(137.75f, 149.0f), Vector2(-70.0f, -92.0f), 6, 0.1f, true);

			//위에보기
			an->CrateAnimation(L"플레이어기본총위상체", Resources::Find<graphics::Texture>(L"플레이어기본총위")
				, Vector2(0.0f, 0.0f), Vector2(123.5f, 149.0f), Vector2(-45.f, -120.0f), 4, 0.2f);
			an->CrateAnimation(L"플레이어기본총위상체좌", Resources::Find<graphics::Texture>(L"플레이어기본총위좌")
				, Vector2(0.0f, 0.0f), Vector2(123.5f, 149.0f), Vector2(-65.f, -120.0f), 4, 0.2f, true);

			//아래보기
			an->CrateAnimation(L"플레이어기본총아래상체", Resources::Find<graphics::Texture>(L"플레이어기본총아래")
				, Vector2(0.0f, 0.0f), Vector2(108.0f, 134.0f), Vector2(-45.f, -64.0f), 1, 0.2f);
			an->CrateAnimation(L"플레이어기본총아래상체좌", Resources::Find<graphics::Texture>(L"플레이어기본총아래좌")
				, Vector2(0.0f, 0.0f), Vector2(108.0f, 134.0f), Vector2(-65.f, -64.0f), 1, 0.2f, true);
			
			//투명(앉기)
			an->CrateAnimation(L"플레이어가만안보임", Resources::Find<graphics::Texture>(L"플레이어_가만")
				, Vector2(800, 0), Vector2(127.72f, 148), Vector2(-50.f, -100.f), 1, 1.f);
			
			//가만어택
			an->CrateAnimation(L"플레이어가만총쏘는중상체", Resources::Find<graphics::Texture>(L"플레이어가만총쏘는중")
				, Vector2(0.0f, 0.0f), Vector2(213.0f, 130.0f), Vector2(-51.0f, -92.0f), 3, 0.1f);
			an->CrateAnimation(L"플레이어가만총쏘는중상체좌", Resources::Find<graphics::Texture>(L"플레이어가만총쏘는중좌")
				, Vector2(0.0f, 0.0f), Vector2(213.0f, 130.0f), Vector2(-153.0f, -92.0f), 3, 0.1f, true);
			an->CrateAnimation(L"플레이어가만총쏘기상체", Resources::Find<graphics::Texture>(L"플레이어가만총쏘기")
				, Vector2(0.0f, 0.0f), Vector2(149.5f, 130.0f), Vector2(-45.0f, -92.0f), 7, 0.05f);
			an->CrateAnimation(L"플레이어가만총쏘기상체좌", Resources::Find<graphics::Texture>(L"플레이어가만총쏘기좌")
				, Vector2(0.0f, 0.0f), Vector2(149.5f, 130.0f), Vector2(-95.0f, -92.0f), 7, 0.05f, true);

			an->GetStartEvent(L"플레이어가만총쏘는중상체") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetStartEvent(L"플레이어가만총쏘는중상체좌") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetCompleteEvent(L"플레이어가만총쏘는중상체") = std::bind(&PlayerScript::ShootEnd, plysc);
			an->GetCompleteEvent(L"플레이어가만총쏘는중상체좌") = std::bind(&PlayerScript::ShootEnd, plysc);

			//점프어택
			an->CrateAnimation(L"플레이어점프총쏘는중상체", Resources::Find<graphics::Texture>(L"플레이어점프총쏘는중")
				, Vector2(0.0f, 0.0f), Vector2(221.0f, 130.0f), Vector2(-51.0f, -92.0f), 3, 0.1f);
			an->CrateAnimation(L"플레이어점프총쏘는중상체좌", Resources::Find<graphics::Texture>(L"플레이어점프총쏘는중좌")
				, Vector2(0.0f, 0.0f), Vector2(221.0f, 130.0f), Vector2(-153.0f, -92.0f), 3, 0.1f, true);
			an->CrateAnimation(L"플레이어점프총쏘기상체", Resources::Find<graphics::Texture>(L"플레이어점프총쏘기")
				, Vector2(0.0f, 0.0f), Vector2(149.5f, 130.0f), Vector2(-51.0f, -92.0f), 7, 0.05f);
			an->CrateAnimation(L"플레이어점프총쏘기상체좌", Resources::Find<graphics::Texture>(L"플레이어점프총쏘기좌")
				, Vector2(0.0f, 0.0f), Vector2(149.5f, 130.0f), Vector2(-95.0f, -92.0f), 7, 0.05f, true);
			
			an->GetStartEvent(L"플레이어점프총쏘는중상체") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetStartEvent(L"플레이어점프총쏘는중상체좌") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetCompleteEvent(L"플레이어점프총쏘는중상체") = std::bind(&PlayerScript::ShootEnd, plysc);
			an->GetCompleteEvent(L"플레이어점프총쏘는중상체좌") = std::bind(&PlayerScript::ShootEnd, plysc);

			//위어택
			an->CrateAnimation(L"플레이어위총쏘는중상체", Resources::Find<graphics::Texture>(L"플레이어위총쏘는중")
				, Vector2(0.0f, 0.0f), Vector2(102.0f, 260.0f), Vector2(-51.0f, -230.0f), 3, 0.1f);
			an->CrateAnimation(L"플레이어위총쏘는중상체좌", Resources::Find<graphics::Texture>(L"플레이어위총쏘는중좌")
				, Vector2(0.0f, 0.0f), Vector2(102.0f, 260.0f), Vector2(-51.0f, -230.0f), 3, 0.1f, true);
			an->CrateAnimation(L"플레이어위총쏘기상체", Resources::Find<graphics::Texture>(L"플레이어위총쏘기")
				, Vector2(0.0f, 0.0f), Vector2(107.0f, 260.0f), Vector2(-51.0f, -230.0f), 7, 0.05f);
			an->CrateAnimation(L"플레이어위총쏘기상체좌", Resources::Find<graphics::Texture>(L"플레이어위총쏘기좌")
				, Vector2(0.0f, 0.0f), Vector2(107.0f, 260.0f), Vector2(-51.0f, -230.0f), 7, 0.05f, true);

			an->GetStartEvent(L"플레이어위총쏘는중상체") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetStartEvent(L"플레이어위총쏘는중상체좌") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetCompleteEvent(L"플레이어위총쏘는중상체") = std::bind(&PlayerScript::ShootEnd, plysc);
			an->GetCompleteEvent(L"플레이어위총쏘는중상체좌") = std::bind(&PlayerScript::ShootEnd, plysc);
			
			//아래어택
			an->CrateAnimation(L"플레이어아래총쏘는중상체", Resources::Find<graphics::Texture>(L"플레이어아래총쏘는중")
				, Vector2(0.0f, 0.0f), Vector2(109.0f, 260.0f), Vector2(-51.0f, -84.0f), 3, 0.1f);
			an->CrateAnimation(L"플레이어아래총쏘는중상체좌", Resources::Find<graphics::Texture>(L"플레이어아래총쏘는중좌")
				, Vector2(0.0f, 0.0f), Vector2(109.0f, 260.0f), Vector2(-51.0f, -84.0f), 3, 0.1f, true);
			an->CrateAnimation(L"플레이어아래총쏘기상체", Resources::Find<graphics::Texture>(L"플레이어아래총쏘기")
				, Vector2(0.0f, 0.0f), Vector2(109.0f, 260.0f), Vector2(-51.0f, -84.0f), 7, 0.05f);
			an->CrateAnimation(L"플레이어아래총쏘기상체좌", Resources::Find<graphics::Texture>(L"플레이어아래총쏘기좌")
				, Vector2(0.0f, 0.0f), Vector2(109.0f, 260.0f), Vector2(-51.0f, -84.0f), 7, 0.05f, true);

			an->GetStartEvent(L"플레이어아래총쏘는중상체") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetStartEvent(L"플레이어아래총쏘는중상체좌") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetCompleteEvent(L"플레이어아래총쏘는중상체") = std::bind(&PlayerScript::ShootEnd, plysc);
			an->GetCompleteEvent(L"플레이어아래총쏘는중상체좌") = std::bind(&PlayerScript::ShootEnd, plysc);

			//수류탄

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
		
		{
			std::ifstream file{ "..\\Resource\\box1.txt" };
			std::string buff;
			Vector2 pos;
			Vector2 size;
			while (file >> buff)
			{
				pos.x = stof(buff);
				file >> buff;
				pos.y = stof(buff);
				file >> buff;
				size.x = stof(buff);
				file >> buff;
				size.y = stof(buff);
				auto block = object::Instantiate<GameObject>(LayerType::Block, pos);
				auto bx = block->AddComponent<BoxCollider2D>();

				bx->setName(L"BackGrounds");
				bx->SetSize(size);
				block->AddComponent<BlockScript>();
				Blocks.push_back(block);
			}
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
		//mapTool
		{
			auto drawBox = object::Instantiate<GameObject>(LayerType::Tool);
			auto bx = drawBox->AddComponent<CircleCollider2D>();
			bx->SetSize(Vector2::One * 0.1);
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
		Scene::Destroy();
	}

	void STAGE1::OnEnter()
	{
	}
	void STAGE1::OnExit() 
	{
	}


}
