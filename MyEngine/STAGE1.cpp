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
			sr->SetTexture(Resources::Find<graphics::Texture>(L"��"));

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
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�޹�潣"));
			
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

			an->CrateAnimation(L"����_�⺻_Move", Resources::Find<graphics::Texture>(L"����_�⺻_Move")
				, Vector2(0, 49)
				, Vector2(842, 707)
				, Vector2(0, 0), 12, 0.1f);
			an->CrateAnimation(L"����_�⺻_Shoot", Resources::Find<graphics::Texture>(L"����_�⺻_Shoot")
				, Vector2(0, 49)
				, Vector2(855, 707)
				, Vector2(0, 0), 12, 0.1f);
			an->CrateAnimation(L"����_Cannon_Depoly", Resources::Find<graphics::Texture>(L"����_Cannon_Depoly")
				, Vector2(0, 50)
				, Vector2(855, 727)
				, Vector2(0, 0), 12, 0.1f);
			an->CrateAnimation(L"����_Cannon_Move", Resources::Find<graphics::Texture>(L"����_Cannon_Move")
				, Vector2(0, 50)
				, Vector2(855, 727)
				, Vector2(0, 0), 12, 0.1f);
			
			an->CrateAnimation(L"����_Cannon_Shoot", Resources::Find<graphics::Texture>(L"����_Cannon_Shoot")
				, Vector2(0, 50)
				, Vector2(855, 727)
				, Vector2(0, 0), 12, 0.1f);
			an->CrateAnimation(L"����_����",Resources::Find<graphics::Texture>(L"����_����")
				, Vector2(0, 50)
				, Vector2(855, 647)
				, Vector2(0, 0), 12, 0.1f);

			an->PlayAnimation(L"����_�⺻_Shoot", true);
		}
		//���� sfx
		{
			auto bossSfx = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
			//���� ��ġ�� ���缭 ����������
			bossSfx->GetComponent<Transform>()->SetPosition(Vector2(5500, 0));
			auto an = bossSfx->AddComponent<Animator>();
			an->CrateAnimation(L"����_sfx", Resources::Find<graphics::Texture>(L"����_SFX")
				, Vector2(0, 50)
				, Vector2(825, 374)
				, Vector2(0, 0), 10, 0.1f);
			an->PlayAnimation(L"����_sfx");
		}
		//Player��ü
		{
			PlayerLowerBody = object::Instantiate<Player>(LayerType::PlayerLowerBody, { 0, 0 });


			auto an = PlayerLowerBody->AddComponent<Animator>();
			auto plysc = PlayerLowerBody->AddComponent<PlayerLowerBodyScript>();
			
			

			auto cd = PlayerLowerBody->AddComponent<BoxCollider2D>();
			cd->SetOffset(Vector2(-50, -50));
			PlayerLowerBody->GetComponent<Transform>()->SetPosition(Vector2(6000, app.getScreen().y / 2.f));


			
			an->CrateAnimation(L"�÷��̾�������ü", Resources::Find<graphics::Texture>(L"�÷��̾�_��_��ü")
				, Vector2(16, 0)
				, Vector2(81.f, 107)
				, Vector2(-40.f, -40.f), 4, 0.1f);
			an->CrateAnimation(L"�÷��̾�������ü", Resources::Find<graphics::Texture>(L"�÷��̾�_��_��ü��")
				, Vector2(16, 0)
				, Vector2(81.f, 107)
				, Vector2(-45.f, -40.f), 4, 0.1f, true);

			an->CrateAnimation(L"�÷��̾����ü", Resources::Find<graphics::Texture>(L"�÷��̾�_����")
				, Vector2(550, 0)
				, Vector2(127.72f, 148)
				, Vector2(-55.f, -85.f), 1, 0.1f);
			an->CrateAnimation(L"�÷��̾����ü��", Resources::Find<graphics::Texture>(L"�÷��̾�_�°���")
				, Vector2(550, 0)
				, Vector2(127.72f, 148)
				, Vector2(-70.f, -85.f), 1, 0.1f,true);

			an->CrateAnimation(L"�÷��̾���̵���ü", Resources::Find<graphics::Texture>(L"�÷��̾��̵�")
				, Vector2(0.0f, 140.f), Vector2(137.75f, 86), Vector2(-55.f, -19.f), 12, 0.1f);
			an->CrateAnimation(L"�÷��̾����̵���ü", Resources::Find<graphics::Texture>(L"�÷��̾����̵�")
				, Vector2(0.0f, 140.f), Vector2(137.75f, 86), Vector2(-70.f, -19.f), 12, 0.1f, true);


			an->CrateAnimation(L"�÷��̾�ɱ����", Resources::Find<graphics::Texture>(L"�÷��̾�ɱ����")
				, Vector2(0.0f, 0.f), Vector2(135.3f, 152), Vector2(-60.f, -109.f), 3, 0.05f);
			an->CrateAnimation(L"�÷��̾�ɱ������", Resources::Find<graphics::Texture>(L"�÷��̾�ɱ������")
				, Vector2(0.0f, 0.f), Vector2(135.3f, 152), Vector2(-60.f, -109.f), 3, 0.05f,true);

			an->CrateAnimation(L"�÷��̾�ɱ��߰�", Resources::Find<graphics::Texture>(L"�÷��̾�ɱ��߰�")
				, Vector2(0.0f, 0.f), Vector2(139.5f, 152), Vector2(-60.f, -109.f), 4, 0.05f);
			an->CrateAnimation(L"�÷��̾�ɱ��߰���", Resources::Find<graphics::Texture>(L"�÷��̾�ɱ��߰���")
				, Vector2(0.0f, 0.f), Vector2(139.5f, 152), Vector2(-60.f, -109.f), 4, 0.05f,true);

			an->CrateAnimation(L"�÷��̾����", Resources::Find<graphics::Texture>(L"�÷��̾����")
				, Vector2(0.0f, 0.0f), Vector2(142.5f, 152), Vector2(-60.f, -109.f), 4, 0.5f);
			an->CrateAnimation(L"�÷��̾������", Resources::Find<graphics::Texture>(L"�÷��̾������")
				, Vector2(0.0f, 0.0f), Vector2(142.5f, 152), Vector2(-60.f, -109.f), 4, 0.5f,true);


			an->CrateAnimation(L"�÷��̾�_����_����", Resources::Find<graphics::Texture>(L"�÷��̾�_����_����")
				, Vector2(0.0f, 0.0f)
				, Vector2(212.f, 125.0f)
				, Vector2(-50, -60), 10, 0.05f);
			an->CrateAnimation(L"�÷��̾�_����_������", Resources::Find<graphics::Texture>(L"�÷��̾�_����_������")
				, Vector2(0.0f, 0.0f)
				, Vector2(211.f, 125.0f)
				, Vector2(-150, -60), 10, 0.05f,true);
			an->CrateAnimation(L"�÷��̾�_����_����ź", Resources::Find<graphics::Texture>(L"�÷��̾�_����_����ź")
				, Vector2(0.0f, 0.0f)
				, Vector2(163.0f, 112.0f)
				, Vector2(-100, -60), 6, 0.05f);
			an->CrateAnimation(L"�÷��̾�_����_����ź��", Resources::Find<graphics::Texture>(L"�÷��̾�_����_����ź��")
				, Vector2(0.0f, 0.0f)
				, Vector2(163.0f, 112.0f)
				, Vector2(-100, -60), 6, 0.05f,true);

			an->CrateAnimation(L"�÷��̾�_����_�̵�", Resources::Find<graphics::Texture>(L"�÷��̾�_����_�̵�")
				, Vector2(0.0f, 0.0f)
				, Vector2(144.0f, 97.f)
				, Vector2(-60, -40), 6, 0.05f);
			an->CrateAnimation(L"�÷��̾�_����_�̵���", Resources::Find<graphics::Texture>(L"�÷��̾�_����_�̵���")
				, Vector2(0.0f, 0.0f)
				, Vector2(144.0f, 97.f)
				, Vector2(-80, -40), 6, 0.05f, true);
			


			an->CrateAnimation(L"�÷��̾�_�����̵�", Resources::Find<graphics::Texture>(L"�÷��̾�_�����̵�")
				, Vector2(0.0f, 0.0f)
				, Vector2(168.f, 134.f)
				, Vector2(-50, -70), 5, 0.05f);
			an->CrateAnimation(L"�÷��̾�_�����̵���", Resources::Find<graphics::Texture>(L"�÷��̾�_�����̵���")
				, Vector2(0.0f, 0.0f)
				, Vector2(168.f, 134.f)
				, Vector2(-120, -70), 5, 0.05f,true);

			an->CrateAnimation(L"�÷��̾�_�����̵�_��", Resources::Find<graphics::Texture>(L"�÷��̾�_�����̵�_��")
				, Vector2(672.f, 0.0f)
				, Vector2(168.f, 134.f)
				, Vector2(-120, -70), 1, 0.05f);
			an->CrateAnimation(L"�÷��̾�_�����̵���_��", Resources::Find<graphics::Texture>(L"�÷��̾�_�����̵���_��")
				, Vector2(672.f, 0.0f)
				, Vector2(168.f, 134.f)
				, Vector2(-120, -70), 1, 0.05f, true);


			an->CrateAnimation(L"�÷��̾�_�����̵�_�⺻��_����", Resources::Find<graphics::Texture>(L"�÷��̾�_�����̵�_�⺻��_����")
				, Vector2(0.0f, 0.0f)
				, Vector2(200.f, 119.f)
				, Vector2(-50, -50), 5, 0.05f);
			an->CrateAnimation(L"�÷��̾�_�����̵�_�⺻��_������", Resources::Find<graphics::Texture>(L"�÷��̾�_�����̵�_�⺻��_������")
				, Vector2(0.0f, 0.0f)
				, Vector2(200.f, 119.f)
				, Vector2(-150, -50), 5, 0.05f, true);


			an->CrateAnimation(L"�÷��̾�_����_��ü", Resources::Find<graphics::Texture>(L"�÷��̾�_����_��ü")
				, Vector2(0.0f, 124.5f)
				, Vector2(123.f, 124.5f)
				, Vector2(-70, -70), 6, 0.1f);
			an->CrateAnimation(L"�÷��̾�_����_��ü��", Resources::Find<graphics::Texture>(L"�÷��̾�_����_��ü��")
				, Vector2(0.0f, 124.5f)
				, Vector2(123.f, 124.5f)
				, Vector2(-60, -70), 6, 0.1f,true);

			an->CrateAnimation(L"�÷��̾�_�̵�_����_��ü", Resources::Find<graphics::Texture>(L"�÷��̾�_�̵�_����_��ü")
				, Vector2(750.0f, 147.5f)
				, Vector2(130.f, 102.5f)
				, Vector2(-60, -38), 6, 0.1f);
			an->CrateAnimation(L"�÷��̾�_�̵�_����_��ü��", Resources::Find<graphics::Texture>(L"�÷��̾�_�̵�_����_��ü��")
				, Vector2(750.0f, 147.5f)
				, Vector2(130.f, 102.5f)
				, Vector2(-70, -38), 6, 0.1f,true);





			an->GetCompleteEvent(L"�÷��̾�ɱ����") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�ɱ������") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�ɱ��߰�") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�ɱ��߰���") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾����") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾������") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);


			an->GetCompleteEvent(L"�÷��̾�_����_����") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�_����_������") = std::bind(&PlayerLowerBodyScript::NextSitAnimation, plysc);
			

			an->PlayAnimation(L"�÷��̾�������ü", true);
			//an->PlayAnimation(L"�÷��̾���̵���ü", true);
			//an->PlayAnimation(L"�÷��̾�ɱ��߰�", true);
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
			//����
			an->CrateAnimation(L"�÷��̾���⺻", Resources::Find<graphics::Texture>(L"�÷��̾�_����")
				, Vector2(10, 0), Vector2(127.72f, 148), Vector2(-50.f, -100.f), 4, 0.1f);
			an->CrateAnimation(L"�÷��̾���⺻��", Resources::Find<graphics::Texture>(L"�÷��̾�_�°���")
				, Vector2(10, 0), Vector2(127.72f, 148), Vector2(-83.f, -100.f), 4, 0.1f, true);

			//�̵�
			an->CrateAnimation(L"�÷��̾��̵���ü", Resources::Find<graphics::Texture>(L"�÷��̾��̵�")
				, Vector2(0.0f, 0.0f), Vector2(137.75f, 113.0f), Vector2(-50.f, -80.f), 12, 0.1f);
			an->CrateAnimation(L"�÷��̾��̵���ü��", Resources::Find<graphics::Texture>(L"�÷��̾����̵�")
				, Vector2(0.0f, 0.0f), Vector2(137.75f, 146.0f), Vector2(-70.0f, -80.f), 12, 0.1f, true);

			//��������
			an->CrateAnimation(L"�÷��̾������", Resources::Find<graphics::Texture>(L"�÷��̾������")
				, Vector2(0.0f, 0.0f), Vector2(126.0f, 139.0f), Vector2(-65.0f, -97.0f), 6, 0.1f);
			an->CrateAnimation(L"�÷��̾��������", Resources::Find<graphics::Texture>(L"�÷��̾��������")
				, Vector2(0.0f, 0.0f), Vector2(126.0f, 139.0f), Vector2(-65.0f, -97.0f), 6, 0.1f, true);
			//�̵�����
			an->CrateAnimation(L"�÷��̾��̵�����", Resources::Find<graphics::Texture>(L"�÷��̾��̵�����")
				, Vector2(764.0f, 0.0f), Vector2(126.0f, 139.0f), Vector2(-60.0f, -87.0f), 6, 0.1f);
			an->CrateAnimation(L"�÷��̾��̵�������", Resources::Find<graphics::Texture>(L"�÷��̾��̵�������")
				, Vector2(764.0f, 0.0f), Vector2(126.0f, 139.0f), Vector2(-65.0f, -87.0f), 6, 0.1f, true);

			//��������
			an->CrateAnimation(L"�÷��̾�⺻������ü", Resources::Find<graphics::Texture>(L"�÷��̾�⺻����")
				, Vector2(0.0f, 0.0f), Vector2(123.5f, 149.0f), Vector2(-45.f, -120.0f), 4, 0.2f);
			an->CrateAnimation(L"�÷��̾�⺻������ü��", Resources::Find<graphics::Texture>(L"�÷��̾�⺻������")
				, Vector2(0.0f, 0.0f), Vector2(123.5f, 149.0f), Vector2(-65.f, -120.0f), 4, 0.2f, true);
			//�Ʒ�����
			an->CrateAnimation(L"�÷��̾�⺻�ѾƷ���ü", Resources::Find<graphics::Texture>(L"�÷��̾�⺻�ѾƷ�")
				, Vector2(0.0f, 0.0f), Vector2(108.0f, 134.0f), Vector2(-45.f, -64.0f), 1, 0.2f);
			an->CrateAnimation(L"�÷��̾�⺻�ѾƷ���ü��", Resources::Find<graphics::Texture>(L"�÷��̾�⺻�ѾƷ���")
				, Vector2(0.0f, 0.0f), Vector2(108.0f, 134.0f), Vector2(-65.f, -64.0f), 1, 0.2f, true);

			//����(�ɱ�)
			an->CrateAnimation(L"�÷��̾���Ⱥ���", Resources::Find<graphics::Texture>(L"�÷��̾�_����")
				, Vector2(800, 0), Vector2(127.72f, 148), Vector2(-50.f, -100.f), 1, 1.f);

			//��������
			an->CrateAnimation(L"�÷��̾���ѽ���߻�ü", Resources::Find<graphics::Texture>(L"�÷��̾���ѽ����")
				, Vector2(0.0f, 0.0f), Vector2(213.0f, 130.0f), Vector2(-51.0f, -92.0f), 3, 0.1f);
			an->CrateAnimation(L"�÷��̾���ѽ���߻�ü��", Resources::Find<graphics::Texture>(L"�÷��̾���ѽ������")
				, Vector2(0.0f, 0.0f), Vector2(213.0f, 130.0f), Vector2(-153.0f, -92.0f), 3, 0.1f, true);
			an->CrateAnimation(L"�÷��̾���ѽ���ü", Resources::Find<graphics::Texture>(L"�÷��̾���ѽ��")
				, Vector2(0.0f, 0.0f), Vector2(149.5f, 130.0f), Vector2(-45.0f, -92.0f), 7, 0.05f);
			an->CrateAnimation(L"�÷��̾���ѽ���ü��", Resources::Find<graphics::Texture>(L"�÷��̾���ѽ����")
				, Vector2(0.0f, 0.0f), Vector2(149.5f, 130.0f), Vector2(-95.0f, -92.0f), 7, 0.05f, true);

			an->GetStartEvent(L"�÷��̾���ѽ���߻�ü") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetStartEvent(L"�÷��̾���ѽ���߻�ü��") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetCompleteEvent(L"�÷��̾���ѽ���߻�ü") = std::bind(&PlayerScript::ShootEnd, plysc);
			an->GetCompleteEvent(L"�÷��̾���ѽ���߻�ü��") = std::bind(&PlayerScript::ShootEnd, plysc);

			//��������
			an->CrateAnimation(L"�÷��̾������ѽ���߻�ü", Resources::Find<graphics::Texture>(L"�÷��̾������ѽ����")
				, Vector2(0.0f, 0.0f), Vector2(221.0f, 130.0f), Vector2(-51.0f, -92.0f), 3, 0.1f);
			an->CrateAnimation(L"�÷��̾������ѽ���߻�ü��", Resources::Find<graphics::Texture>(L"�÷��̾������ѽ������")
				, Vector2(0.0f, 0.0f), Vector2(221.0f, 130.0f), Vector2(-153.0f, -92.0f), 3, 0.1f, true);
			an->CrateAnimation(L"�÷��̾������ѽ���ü", Resources::Find<graphics::Texture>(L"�÷��̾������ѽ��")
				, Vector2(0.0f, 0.0f), Vector2(149.5f, 130.0f), Vector2(-51.0f, -92.0f), 7, 0.05f);
			an->CrateAnimation(L"�÷��̾������ѽ���ü��", Resources::Find<graphics::Texture>(L"�÷��̾������ѽ����")
				, Vector2(0.0f, 0.0f), Vector2(149.5f, 130.0f), Vector2(-95.0f, -92.0f), 7, 0.05f, true);

			an->GetStartEvent(L"�÷��̾������ѽ���߻�ü") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetStartEvent(L"�÷��̾������ѽ���߻�ü��") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetCompleteEvent(L"�÷��̾������ѽ���߻�ü") = std::bind(&PlayerScript::ShootEnd, plysc);
			an->GetCompleteEvent(L"�÷��̾������ѽ���߻�ü��") = std::bind(&PlayerScript::ShootEnd, plysc);

			//������
			an->CrateAnimation(L"�÷��̾����ѽ���߻�ü", Resources::Find<graphics::Texture>(L"�÷��̾����ѽ����")
				, Vector2(0.0f, 0.0f), Vector2(102.0f, 260.0f), Vector2(-51.0f, -230.0f), 3, 0.1f);
			an->CrateAnimation(L"�÷��̾����ѽ���߻�ü��", Resources::Find<graphics::Texture>(L"�÷��̾����ѽ������")
				, Vector2(0.0f, 0.0f), Vector2(102.0f, 260.0f), Vector2(-51.0f, -230.0f), 3, 0.1f, true);
			an->CrateAnimation(L"�÷��̾����ѽ���ü", Resources::Find<graphics::Texture>(L"�÷��̾����ѽ��")
				, Vector2(0.0f, 0.0f), Vector2(107.0f, 260.0f), Vector2(-51.0f, -230.0f), 7, 0.05f);
			an->CrateAnimation(L"�÷��̾����ѽ���ü��", Resources::Find<graphics::Texture>(L"�÷��̾����ѽ����")
				, Vector2(0.0f, 0.0f), Vector2(107.0f, 260.0f), Vector2(-51.0f, -230.0f), 7, 0.05f, true);

			an->GetStartEvent(L"�÷��̾����ѽ���߻�ü") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetStartEvent(L"�÷��̾����ѽ���߻�ü��") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetCompleteEvent(L"�÷��̾����ѽ���߻�ü") = std::bind(&PlayerScript::ShootEnd, plysc);
			an->GetCompleteEvent(L"�÷��̾����ѽ���߻�ü��") = std::bind(&PlayerScript::ShootEnd, plysc);

			//�Ʒ�����
			an->CrateAnimation(L"�÷��̾�Ʒ��ѽ���߻�ü", Resources::Find<graphics::Texture>(L"�÷��̾�Ʒ��ѽ����")
				, Vector2(0.0f, 0.0f), Vector2(109.0f, 260.0f), Vector2(-51.0f, -84.0f), 3, 0.1f);
			an->CrateAnimation(L"�÷��̾�Ʒ��ѽ���߻�ü��", Resources::Find<graphics::Texture>(L"�÷��̾�Ʒ��ѽ������")
				, Vector2(0.0f, 0.0f), Vector2(109.0f, 260.0f), Vector2(-51.0f, -84.0f), 3, 0.1f, true);
			an->CrateAnimation(L"�÷��̾�Ʒ��ѽ���ü", Resources::Find<graphics::Texture>(L"�÷��̾�Ʒ��ѽ��")
				, Vector2(0.0f, 0.0f), Vector2(109.0f, 260.0f), Vector2(-51.0f, -84.0f), 7, 0.05f);
			an->CrateAnimation(L"�÷��̾�Ʒ��ѽ���ü��", Resources::Find<graphics::Texture>(L"�÷��̾�Ʒ��ѽ����")
				, Vector2(0.0f, 0.0f), Vector2(109.0f, 260.0f), Vector2(-51.0f, -84.0f), 7, 0.05f, true);

			an->GetStartEvent(L"�÷��̾�Ʒ��ѽ���߻�ü") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetStartEvent(L"�÷��̾�Ʒ��ѽ���߻�ü��") = std::bind(&PlayerScript::ShootBullet, plysc);
			an->GetCompleteEvent(L"�÷��̾�Ʒ��ѽ���߻�ü") = std::bind(&PlayerScript::ShootEnd, plysc);
			an->GetCompleteEvent(L"�÷��̾�Ʒ��ѽ���߻�ü��") = std::bind(&PlayerScript::ShootEnd, plysc);

			//����ź
			an->CrateAnimation(L"�÷��̾������ź", Resources::Find<graphics::Texture>(L"�÷��̾������ź")
				, Vector2(0.0f, 0.0f), Vector2(139.0f, 140.0f), Vector2(-51.0f, -80.0f), 6, 0.1f);
			an->CrateAnimation(L"�÷��̾������ź��", Resources::Find<graphics::Texture>(L"�÷��̾������ź��")
				, Vector2(0.0f, 0.0f), Vector2(139.0f, 140.0f), Vector2(-51.0f, -80.0f), 6, 0.1f, true);
			an->CrateAnimation(L"�÷��̾���������ź", Resources::Find<graphics::Texture>(L"�÷��̾���������ź")
				, Vector2(0.0f, 0.0f), Vector2(139.0f, 140.0f), Vector2(-61.0f, -90.0f), 6, 0.1f);
			an->CrateAnimation(L"�÷��̾���������ź��", Resources::Find<graphics::Texture>(L"�÷��̾���������ź��")
				, Vector2(0.0f, 0.0f), Vector2(139.0f, 140.0f), Vector2(-61.0f, -90.0f), 6, 0.1f, true);

			an->GetCompleteEvent(L"�÷��̾������ź") = std::bind(&PlayerScript::ThrowGrenade, plysc);
			an->GetCompleteEvent(L"�÷��̾������ź��") = std::bind(&PlayerScript::ThrowGrenade, plysc);
			an->GetCompleteEvent(L"�÷��̾���������ź") = std::bind(&PlayerScript::ThrowGrenade, plysc);
			an->GetCompleteEvent(L"�÷��̾���������ź��") = std::bind(&PlayerScript::ThrowGrenade, plysc);


			an->PlayAnimation(L"�÷��̾���⺻", true);
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
			//�̰� �˴� ��ũ��Ʈ�� ������ ������
			an->CrateAnimation(L"��_idle", Resources::Find<graphics::Texture>(L"��_idle")
				, Vector2(0, 0)
				, Vector2(200, 150)
				, Vector2(-60, -50), 7, 0.1f);
			an->CrateAnimation(L"��_idle_��", Resources::Find<graphics::Texture>(L"��_idle_��")
				, Vector2(0, 0)
				, Vector2(200, 150)
				, Vector2(-60, -50), 7, 0.1f, true);

			an->CrateAnimation(L"��_walk", Resources::Find<graphics::Texture>(L"��_walk")
				, Vector2(0, 0)
				, Vector2(200, 146)
				, Vector2(-60, -50), 7, 0.1f);
			an->CrateAnimation(L"��_walk_��", Resources::Find<graphics::Texture>(L"��_walk_��")
				, Vector2(0, 0)
				, Vector2(200, 146)
				, Vector2(-60, -50), 7, 0.1f, true);

			an->CrateAnimation(L"��_attack_�⺻1", Resources::Find<graphics::Texture>(L"��_attack")
				, Vector2(50, 0)
				, Vector2(177, 170)
				, Vector2(-60, -50), 5, 0.1f);
			an->CrateAnimation(L"��_attack_�⺻2", Resources::Find<graphics::Texture>(L"��_attack")
				, Vector2(938, 0)
				, Vector2(243, 170)
				, Vector2(-60, -50), 4, 0.1f);
			an->CrateAnimation(L"��_attack_��_�⺻1", Resources::Find<graphics::Texture>(L"��_attack_��")
				, Vector2(50, 0)
				, Vector2(177, 170)
				, Vector2(-60, -50), 5, 0.1f);
			an->CrateAnimation(L"��_attack_��_�⺻2", Resources::Find<graphics::Texture>(L"��_attack_��")
				, Vector2(938, 0)
				, Vector2(243, 170)
				, Vector2(-60, -50), 4, 0.1f);

			an->GetCompleteEvent(L"��_attack_�⺻1") = std::bind(&EnemyScript::NexTAnimation, es);
			an->GetCompleteEvent(L"��_attack_�⺻2") = std::bind(&EnemyScript::NexTAnimation, es);
			an->GetCompleteEvent(L"��_attack_��_�⺻1") = std::bind(&EnemyScript::NexTAnimation, es);
			an->GetCompleteEvent(L"��_attack_��_�⺻2") = std::bind(&EnemyScript::NexTAnimation, es);

			an->PlayAnimation(L"��_walk", true);
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

		//�÷��̾�� �տ��ִ� ���
		{
			auto frontBackground = object::Instantiate<GameObject>(LayerType::FrontGround, { 5576, 691 });
			auto sr = frontBackground->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"����Ա�����1"));
		}
		{
			auto frontBackground = object::Instantiate<GameObject>(LayerType::FrontGround, { 6050, 450 });
			auto sr = frontBackground->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"����Ա�����2"));
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
		//SoundManager::GetInstance()->playSound(L"stage1���κ��", SoundManager::SoundType::BACKGROUND);
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
