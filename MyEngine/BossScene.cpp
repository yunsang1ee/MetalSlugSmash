#include "BossScene.h"
#include "ysGameObject.h"
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
#include <ysAudioSource.h>
#include "WallScript.h"
#include "BossSfxScript.h"
#include "BossScript.h"
#include "STAGE1.h"
#include "YSapplication.h"
using namespace ys;

extern ys::Application app;
ys::BossScene::BossScene()
{
}

ys::BossScene::~BossScene()
{
}

void ys::BossScene::Init()
{
	
	//�÷���
	{
		std::ifstream file{ "..\\Resource\\box2.txt" };
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
	//��
	{
		std::ifstream file{ "..\\Resource\\Wall2.txt" };
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
			auto block = object::Instantiate<GameObject>(LayerType::Wall, pos);
			auto bx = block->AddComponent<BoxCollider2D>();

			bx->setName(L"Wall");
			bx->SetSize(size);
			block->AddComponent<WallScript>();
			Walls.push_back(block);
		}
	}
	{
		auto drawBox = object::Instantiate<GameObject>(LayerType::Tool, Vector2(0, 0));
		auto ds = drawBox->AddComponent<drawBoxScript>();

	}
	Scene::Init();
}

void ys::BossScene::Update()
{
	Scene::Update();
}

void ys::BossScene::LateUpdate()
{
	Scene::LateUpdate();
}

void ys::BossScene::Render(HDC hDC, const int& index)
{
	Scene::Render(hDC,index);
}

void ys::BossScene::Destroy()
{
	Scene::Destroy();
}

void ys::BossScene::OnEnter()
{
	player = STAGE1::GetPlayer();
	PlayerLowerBody = STAGE1::GetPlayerLow();
	camera = STAGE1::GetCamera();

	{
		PlayerLowerBody->GetComponent<Transform>()->SetPosition(Vector2(app.getScreenf().x * 9 / 10.0f, app.getScreenf().y / 5.0f));
	}
	{
		auto background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, 0));
		auto sr = background->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"�������"));
		auto bs = background->AddComponent<BackGroundScript>();
	}
	//boss
	{
		boss = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
		auto an = boss->AddComponent<Animator>();
		auto es = boss->AddComponent<BossScript>();
		auto cd = boss->AddComponent<BoxCollider2D>();

		cd->SetSize(Vector2(9, 7.5f));
		boss->GetComponent<Transform>()->SetPosition(Vector2(200, 250));

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
		an->CrateAnimation(L"����_����", Resources::Find<graphics::Texture>(L"����_����")
			, Vector2(0, 50)
			, Vector2(855, 647)
			, Vector2(0, 0), 12, 0.1f);

		an->PlayAnimation(L"����_�⺻_Shoot", true);
	}
	//���� sfx
	{
		auto bossSfx = object::Instantiate<GameObject>(LayerType::Particle, Vector2(0, 0));
		bossSfx->AddComponent<BossSfxScript>()->SetBoss(boss);

		auto an = bossSfx->AddComponent<Animator>();
		an->CrateAnimation(L"����_sfx", Resources::Find<graphics::Texture>(L"����_SFX")
			, Vector2(0, 50)
			, Vector2(825, 374)
			, Vector2(150, -130), 10, 0.1f);

		an->PlayAnimation(L"����_sfx");
	}
	{
		auto bossSfx = object::Instantiate<GameObject>(LayerType::Particle, Vector2(0, 0));
		bossSfx->AddComponent<BossSfxScript>()->SetBoss(boss);
		auto an = bossSfx->AddComponent<Animator>();
		an->CrateAnimation(L"����_waves", Resources::Find<graphics::Texture>(L"����_waves")
			, Vector2(15, 0)
			, Vector2(930, 259)
			, Vector2(-30, 500), 10, 0.1f);
		an->PlayAnimation(L"����_waves");
	}
	{
		auto bossBullet = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
		auto an = bossBullet->AddComponent<Animator>();
		auto bs = bossBullet->AddComponent<BulletScript>();
		auto cd = bossBullet->AddComponent<BoxCollider2D>();
		cd->SetSize(Vector2(1, 1));
		bossBullet->GetComponent<Transform>()->SetPosition(Vector2(100, 0));

		an->CrateAnimation(L"����_�Ѿ�", Resources::Find<graphics::Texture>(L"����_�Ѿ�")
			, Vector2(0, 0)
			, Vector2(16, 16)
			, Vector2(0, 0), 1, 0.1f);
		an->PlayAnimation(L"����_�Ѿ�", true);


	}
	{
		camera = object::Instantiate<GameObject>(LayerType::Camera);
		renderer::mainCamera = camera->AddComponent<Camera>();
		renderer::mainCamera;
		camera->GetComponent<Camera>()->SetMinMax(Vector2(650, 500), Vector2(3350, 1225));
		camera->AddComponent<CameraScript>();
		auto ad = camera->AddComponent<AudioSource>();
		ad->SetClip(Resources::Find<AudioClip>(L"stage1���κ��"));
		ad->SetLoop(true);
	}
}

void ys::BossScene::OnExit()
{
}
