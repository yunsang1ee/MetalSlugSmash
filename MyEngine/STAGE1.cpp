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
			auto background = object::Instantiate<GameObject>(LayerType::BackBackGround, Vector2(9000, -250));

			auto sr = background->AddComponent<SpriteRenderer>();

			sr->SetTexture(Resources::Find<graphics::Texture>(L"�޹�潣"));
			
			auto bs = background->AddComponent<BackGroundScript>();
			bs->SetParallax(0);
		}
		
		//Player��ü
		{
			playerLowerBody = object::Instantiate<Player>(LayerType::PlayerLowerBody, { 0, 0 });


			auto an = playerLowerBody->AddComponent<Animator>();
			auto plysc = playerLowerBody->AddComponent<PlayerLowerBodyScript>();
			
			

			auto cd = playerLowerBody->AddComponent<BoxCollider2D>();
			cd->SetOffset(Vector2(-50, -50));
			playerLowerBody->GetComponent<Transform>()->SetPosition(Vector2(10000, app.getScreen().y / 2.f));


			
			an->CrateAnimation(L"�÷��̾�������ü", Resources::Find<graphics::Texture>(L"�÷��̾���_��_��ü")
				, Vector2(0, 0), Vector2(125.f, 155), Vector2(-55.f, -85.f), 4, 0.1f);
			an->CrateAnimation(L"�÷��̾�������ü", Resources::Find<graphics::Texture>(L"�÷��̾���_��_��ü")
				, Vector2(550, 0), Vector2(125.f, 155), Vector2(-55.f, -85.f), 4, 0.1f,true);

			an->CrateAnimation(L"�÷��̾����ü", Resources::Find<graphics::Texture>(L"�÷��̾�_����")
				, Vector2(550, 0), Vector2(127.72f, 148), Vector2(-55.f, -85.f), 1, 0.1f);
			an->CrateAnimation(L"�÷��̾����ü��", Resources::Find<graphics::Texture>(L"�÷��̾�_�°���")
				, Vector2(550, 0), Vector2(127.72f, 148), Vector2(-55.f, -85.f), 1, 0.1f,true);

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
			

			an->PlayAnimation(L"�÷��̾�������ü", false);
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
			


			
			
			auto an = player->AddComponent<Animator>();
			an->CrateAnimation(L"�÷��̾���⺻", Resources::Find<graphics::Texture>(L"�÷��̾�_����")
				, Vector2(10, 0)
				, Vector2(127.72f, 148)
				, Vector2(-50.f, -100.f), 4, 0.1f);
			an->CrateAnimation(L"�÷��̾���⺻��", Resources::Find<graphics::Texture>(L"�÷��̾�_�°���")
				, Vector2(10, 0)
				, Vector2(127.72f, 148)
				, Vector2(-83.f, -100.f), 4, 0.1f, true);
			an->CrateAnimation(L"�÷��̾���̵���ü", Resources::Find<graphics::Texture>(L"�÷��̾��̵�")
				, Vector2(0.0f, 0.0f)
				, Vector2(137.75f, 113.0f)
				, Vector2(-50.f,-80.f), 12, 0.1f);
			an->CrateAnimation(L"�÷��̾����̵���ü", Resources::Find<graphics::Texture>(L"�÷��̾����̵�")
				, Vector2(0.0f, 0.0f)
				, Vector2(137.75f, 146.0f)
				, Vector2(-70.0f, -80.f), 12, 0.1f, true); //�ణ�� ���ڿ��������� ����
			an->CrateAnimation(L"�÷��̾�⺻������ü", Resources::Find<graphics::Texture>(L"�÷��̾�⺻����")
				, Vector2(0.0f, 0.0f)
				, Vector2(123.5f, 149.0f)
				, Vector2(-45.f, -120.0f), 4, 0.1f);
			an->CrateAnimation(L"�÷��̾�⺻������ü��", Resources::Find<graphics::Texture>(L"�÷��̾�⺻������")
				, Vector2(0.0f, 0.0f)
				, Vector2(123.5f, 149.0f)
				, Vector2(-65.f, -120.0f), 4, 0.1f, true);
			an->CrateAnimation(L"�÷��̾���Ⱥ���", Resources::Find<graphics::Texture>(L"�÷��̾�_����")
				, Vector2(800, 0)
				, Vector2(127.72f, 148)
				, Vector2(-50.f, -100.f), 1, 1.f);
			



			an->CrateAnimation(L"�÷��̾�_�⺻��_�����_ȭ��", Resources::Find<graphics::Texture>(L"�÷��̾�_�⺻��_�����")
				, Vector2(0, 0)
				, Vector2(200, 110)
				, Vector2(-50.f, -75.f), 3, 0.05f);
			an->CrateAnimation(L"�÷��̾�_�⺻��_�����", Resources::Find<graphics::Texture>(L"�÷��̾�_�⺻��_�����")
				, Vector2(600, 0)
				, Vector2(145.5f, 110)
				, Vector2(-50.f, -100.f), 7, 0.05f);
			an->CrateAnimation(L"�÷��̾�_�⺻��_�����_����_ȭ��", Resources::Find<graphics::Texture>(L"�÷��̾�_�⺻��_�����")
				, Vector2(1620, 0)
				, Vector2(200, 110.f)
				, Vector2(-50.f, -80.f), 3, 0.05f);
			an->CrateAnimation(L"�÷��̾�_�⺻��_�����_����", Resources::Find<graphics::Texture>(L"�÷��̾�_�⺻��_�����")
				, Vector2(2210, 0)
				, Vector2(144.9f, 110.f)
				, Vector2(-50.f, -80.f), 7, 0.05f);


			an->CrateAnimation(L"�÷��̾�_�⺻��_�°���_ȭ��", Resources::Find<graphics::Texture>(L"�÷��̾�_�⺻��_�°���")
				, Vector2(0, 0)
				, Vector2(200, 110)
				, Vector2(-50.f, -75.f), 3, 0.05f, true);
			an->CrateAnimation(L"�÷��̾�_�⺻��_�°���", Resources::Find<graphics::Texture>(L"�÷��̾�_�⺻��_�°���")
				, Vector2(600, 0)
				, Vector2(145.5f, 110)
				, Vector2(-50.f, -100.f), 7, 0.05f, true);
			an->CrateAnimation(L"�÷��̾�_�⺻��_�°���_����_ȭ��", Resources::Find<graphics::Texture>(L"�÷��̾�_�⺻��_�°���")
				, Vector2(1620, 0)
				, Vector2(200, 110.f)
				, Vector2(-140.f, -80.f), 3, 0.05f, true);
			an->CrateAnimation(L"�÷��̾�_�⺻��_�°���_����", Resources::Find<graphics::Texture>(L"�÷��̾�_�⺻��_�°���")
				, Vector2(2210, 0)
				, Vector2(144.9f, 110.f)
				, Vector2(-50.f, -80.f), 7, 0.05f, true);

			an->GetCompleteEvent(L"�÷��̾�_�⺻��_�����_ȭ��") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�_�⺻��_�����") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�_�⺻��_�����_����_ȭ��") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�_�⺻��_�����_����") = std::bind(&PlayerScript::NextAnimation, plysc);

			an->GetCompleteEvent(L"�÷��̾�_�⺻��_�°���_ȭ��") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�_�⺻��_�°���") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�_�⺻��_�°���_����_ȭ��") = std::bind(&PlayerScript::NextAnimation, plysc);
			an->GetCompleteEvent(L"�÷��̾�_�⺻��_�°���_����") = std::bind(&PlayerScript::NextAnimation, plysc);

			an->PlayAnimation(L"�÷��̾�_�⺻��_�°���_ȭ��", true);
			
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
