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
#include "ysSoundManager.h"
#include <ysAudioListener.h>

extern ys::Application app;
namespace ys
{
	ys::STAGE1::STAGE1()
	{
	}

	ys::STAGE1::~STAGE1()
	{
	}
	void ys::STAGE1::Init()
	{
		CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::Block, true);
		CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::BackGround, true);
		CollisionManager::CollisionLayerCheck(LayerType::Enemy, LayerType::Projectile, true);
		CollisionManager::CollisionLayerCheck(LayerType::Enemy, LayerType::Block, true);
		CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::Block, true);
		CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::BackGround, true);
	
		CollisionManager::CollisionLayerCheck(LayerType::Block, LayerType::Tool, true);
	
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
			backBackground = object::Instantiate<GameObject>(LayerType::BackBackGround, Vector2(9000, -250));

			auto sr = backBackground->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"뒷배경숲"));
			
			auto bs = backBackground->AddComponent<BackGroundScript>();
			bs->SetParallax(0);
		}
		//boss
		{
			auto boss = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
			auto an = boss->AddComponent<Animator>();
			auto es = boss->AddComponent<EnemyScript>();
			auto cd = boss->AddComponent<BoxCollider2D>();
			boss->GetComponent<Transform>()->SetPosition(Vector2(5500, 0));

			an->CrateAnimation(L"보스_기본_Move", Resources::Find<graphics::Texture>(L"보스_기본_Move")
				, Vector2(0, 49)
				, Vector2(842, 707)
				, Vector2(0, 0), 12, 0.1f);
			an->CrateAnimation(L"보스_기본_Shoot", Resources::Find<graphics::Texture>(L"보스_기본_Shoot")
				, Vector2(0, 49)
				, Vector2(855, 707)
				, Vector2(0, 0), 12, 0.1f);
			an->CrateAnimation(L"보스_Cannon_Depoly", Resources::Find<graphics::Texture>(L"보스_Cannon_Depoly")
				, Vector2(0, 50)
				, Vector2(855, 727)
				, Vector2(0, 0), 12, 0.1f);
			an->CrateAnimation(L"보스_Cannon_Move", Resources::Find<graphics::Texture>(L"보스_Cannon_Move")
				, Vector2(0, 50)
				, Vector2(855, 727)
				, Vector2(0, 0), 12, 0.1f);
			
			an->CrateAnimation(L"보스_Cannon_Shoot", Resources::Find<graphics::Texture>(L"보스_Cannon_Shoot")
				, Vector2(0, 50)
				, Vector2(855, 727)
				, Vector2(0, 0), 12, 0.1f);
			an->CrateAnimation(L"보스_죽음",Resources::Find<graphics::Texture>(L"보스_죽음")
				, Vector2(0, 50)
				, Vector2(855, 647)
				, Vector2(0, 0), 12, 0.1f);

			an->PlayAnimation(L"보스_기본_Shoot", true);
		}
		//보스 sfx
		{
			auto bossSfx = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
			//보스 위치에 맞춰서 맞춰져야함
			bossSfx->GetComponent<Transform>()->SetPosition(Vector2(5500, 0));
			auto an = bossSfx->AddComponent<Animator>();
			an->CrateAnimation(L"보스_sfx", Resources::Find<graphics::Texture>(L"보스_SFX")
				, Vector2(0, 50)
				, Vector2(825, 374)
				, Vector2(0, 0), 10, 0.1f);
			an->PlayAnimation(L"보스_sfx");
		}
		//Player하체
		{
			PlayerLowerBody = object::Instantiate<Player>(LayerType::PlayerLowerBody, { 0, 0 });


			auto an = PlayerLowerBody->AddComponent<Animator>();
			auto plysc = PlayerLowerBody->AddComponent<PlayerLowerBodyScript>();
			
			

			auto cd = PlayerLowerBody->AddComponent<BoxCollider2D>();
			cd->SetOffset(Vector2(-50, -50));
			PlayerLowerBody->GetComponent<Transform>()->SetPosition(Vector2(6000, app.getScreen().y / 2.f));


			
			an->CrateAnimation(L"플레이어위우하체", Resources::Find<graphics::Texture>(L"플레이어_위_하체")
				, Vector2(16, 0)
				, Vector2(81.f, 107)
				, Vector2(-40.f, -40.f), 4, 0.1f);
			an->CrateAnimation(L"플레이어위좌하체", Resources::Find<graphics::Texture>(L"플레이어_위_하체좌")
				, Vector2(16, 0)
				, Vector2(81.f, 107)
				, Vector2(-45.f, -40.f), 4, 0.1f, true);

			an->CrateAnimation(L"플레이어가만하체", Resources::Find<graphics::Texture>(L"플레이어_가만")
				, Vector2(550, 0)
				, Vector2(127.72f, 148)
				, Vector2(-55.f, -85.f), 1, 0.1f);
			an->CrateAnimation(L"플레이어가만하체좌", Resources::Find<graphics::Texture>(L"플레이어_좌가만")
				, Vector2(550, 0)
				, Vector2(127.72f, 148)
				, Vector2(-70.f, -85.f), 1, 0.1f,true);

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
			

			an->PlayAnimation(L"플레이어위좌하체", true);
			//an->PlayAnimation(L"플레이어우이동하체", true);
			//an->PlayAnimation(L"플레이어앉기중간", true);
			auto rb = PlayerLowerBody->AddComponent<RigidBody>();
			rb->SetGravity(Vector2::Down * 3.0f);
			ys::object::DontDestroyOnLoad(PlayerLowerBody);
		}

		//Player
		{
			player = object::Instantiate<Player>(LayerType::PlayerTop, { 0, 0 });
			auto plysc = player->AddComponent<PlayerScript>();

			plysc->SetLowerBody(PlayerLowerBody);

			auto an = player->AddComponent<Animator>();
			//가만
			an->CrateAnimation(L"플레이어가만기본", Resources::Find<graphics::Texture>(L"플레이어_가만")
				, Vector2(10, 0), Vector2(127.72f, 148), Vector2(-50.f, -100.f), 4, 0.1f);
			an->CrateAnimation(L"플레이어가만기본좌", Resources::Find<graphics::Texture>(L"플레이어_좌가만")
				, Vector2(10, 0), Vector2(127.72f, 148), Vector2(-83.f, -100.f), 4, 0.1f, true);

			//이동
			an->CrateAnimation(L"플레이어이동상체", Resources::Find<graphics::Texture>(L"플레이어이동")
				, Vector2(0.0f, 0.0f), Vector2(137.75f, 113.0f), Vector2(-50.f, -80.f), 12, 0.1f);
			an->CrateAnimation(L"플레이어이동상체좌", Resources::Find<graphics::Texture>(L"플레이어좌이동")
				, Vector2(0.0f, 0.0f), Vector2(137.75f, 146.0f), Vector2(-70.0f, -80.f), 12, 0.1f, true);

			//가만점프
			an->CrateAnimation(L"플레이어가만점프", Resources::Find<graphics::Texture>(L"플레이어가만점프")
				, Vector2(0.0f, 0.0f), Vector2(126.0f, 139.0f), Vector2(-65.0f, -97.0f), 6, 0.1f);
			an->CrateAnimation(L"플레이어가만점프좌", Resources::Find<graphics::Texture>(L"플레이어가만점프좌")
				, Vector2(0.0f, 0.0f), Vector2(126.0f, 139.0f), Vector2(-65.0f, -97.0f), 6, 0.1f, true);
			//이동점프
			an->CrateAnimation(L"플레이어이동점프", Resources::Find<graphics::Texture>(L"플레이어이동점프")
				, Vector2(764.0f, 0.0f), Vector2(126.0f, 139.0f), Vector2(-60.0f, -87.0f), 6, 0.1f);
			an->CrateAnimation(L"플레이어이동점프좌", Resources::Find<graphics::Texture>(L"플레이어이동점프좌")
				, Vector2(764.0f, 0.0f), Vector2(126.0f, 139.0f), Vector2(-65.0f, -87.0f), 6, 0.1f, true);

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
			an->CrateAnimation(L"플레이어가만수류탄", Resources::Find<graphics::Texture>(L"플레이어가만수류탄")
				, Vector2(0.0f, 0.0f), Vector2(139.0f, 140.0f), Vector2(-51.0f, -80.0f), 6, 0.1f);
			an->CrateAnimation(L"플레이어가만수류탄좌", Resources::Find<graphics::Texture>(L"플레이어가만수류탄좌")
				, Vector2(0.0f, 0.0f), Vector2(139.0f, 140.0f), Vector2(-51.0f, -80.0f), 6, 0.1f, true);
			an->CrateAnimation(L"플레이어점프수류탄", Resources::Find<graphics::Texture>(L"플레이어점프수류탄")
				, Vector2(0.0f, 0.0f), Vector2(139.0f, 140.0f), Vector2(-61.0f, -90.0f), 6, 0.1f);
			an->CrateAnimation(L"플레이어점프수류탄좌", Resources::Find<graphics::Texture>(L"플레이어점프수류탄좌")
				, Vector2(0.0f, 0.0f), Vector2(139.0f, 140.0f), Vector2(-61.0f, -90.0f), 6, 0.1f, true);

			an->GetCompleteEvent(L"플레이어가만수류탄") = std::bind(&PlayerScript::ThrowGrenade, plysc);
			an->GetCompleteEvent(L"플레이어가만수류탄좌") = std::bind(&PlayerScript::ThrowGrenade, plysc);
			an->GetCompleteEvent(L"플레이어점프수류탄") = std::bind(&PlayerScript::ThrowGrenade, plysc);
			an->GetCompleteEvent(L"플레이어점프수류탄좌") = std::bind(&PlayerScript::ThrowGrenade, plysc);


			an->PlayAnimation(L"플레이어가만기본", true);
		}
		
		//Enemy
		{
			auto enemy = object::Instantiate<GameObject>(LayerType::Enemy, { 0,0 });
			enemy->GetComponent<Transform>()->SetPosition(Vector2(5750, 300));
			auto es = enemy->AddComponent<EnemyScript>();
			auto an = enemy->AddComponent<Animator>();
			auto rb = enemy->AddComponent<RigidBody>();
			auto cd = enemy->AddComponent<BoxCollider2D>();

			
			cd->SetOffset(Vector2(-30, -25));
			cd->SetSize(Vector2(1.5f, 1.25f));
			//이걸 죄다 스크립트에 넣으면 좋을듯
			an->CrateAnimation(L"게_idle", Resources::Find<graphics::Texture>(L"게_idle")
				, Vector2(0, 0)
				, Vector2(200, 150)
				, Vector2(-60, -50), 7, 0.1f);
			an->CrateAnimation(L"게_idle_좌", Resources::Find<graphics::Texture>(L"게_idle_좌")
				, Vector2(0, 0)
				, Vector2(200, 150)
				, Vector2(-60, -50), 7, 0.1f, true);

			an->CrateAnimation(L"게_walk", Resources::Find<graphics::Texture>(L"게_walk")
				, Vector2(0, 0)
				, Vector2(200, 146)
				, Vector2(-60, -50), 7, 0.1f);
			an->CrateAnimation(L"게_walk_좌", Resources::Find<graphics::Texture>(L"게_walk_좌")
				, Vector2(0, 0)
				, Vector2(200, 146)
				, Vector2(-60, -50), 7, 0.1f, true);

			an->CrateAnimation(L"게_attack_기본1", Resources::Find<graphics::Texture>(L"게_attack")
				, Vector2(50, 0)
				, Vector2(177, 170)
				, Vector2(-60, -50), 5, 0.1f);
			an->CrateAnimation(L"게_attack_기본2", Resources::Find<graphics::Texture>(L"게_attack")
				, Vector2(938, 0)
				, Vector2(243, 170)
				, Vector2(-60, -50), 4, 0.1f);
			an->CrateAnimation(L"게_attack_좌_기본1", Resources::Find<graphics::Texture>(L"게_attack_좌")
				, Vector2(50, 0)
				, Vector2(177, 170)
				, Vector2(-60, -50), 5, 0.1f);
			an->CrateAnimation(L"게_attack_좌_기본2", Resources::Find<graphics::Texture>(L"게_attack_좌")
				, Vector2(938, 0)
				, Vector2(243, 170)
				, Vector2(-60, -50), 4, 0.1f);

			an->GetCompleteEvent(L"게_attack_기본1") = std::bind(&EnemyScript::NexTAnimation, es);
			an->GetCompleteEvent(L"게_attack_기본2") = std::bind(&EnemyScript::NexTAnimation, es);
			an->GetCompleteEvent(L"게_attack_좌_기본1") = std::bind(&EnemyScript::NexTAnimation, es);
			an->GetCompleteEvent(L"게_attack_좌_기본2") = std::bind(&EnemyScript::NexTAnimation, es);

			an->PlayAnimation(L"게_walk", true);
		}
		
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
			camera->AddComponent<AudioListener>();
		}
		//mapTool
		{
			auto drawBox = object::Instantiate<GameObject>(LayerType::Tool);
			auto bx = drawBox->AddComponent<CircleCollider2D>();
			bx->SetSize(Vector2::One * 0.1);
			drawBox->AddComponent<drawBoxScript>();
		}
		//SoundManager::GetInstance()->playSound(L"stage1메인브금", SoundManager::SoundType::BACKGROUND);
		//SoundManager::GetInstance()->GetBackGroundChannel()->setVolume(0.5f);
		
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
		Scene::Destroy();
	}

	void STAGE1::OnEnter()
	{
	}
	void STAGE1::OnExit() 
	{
	}


}
