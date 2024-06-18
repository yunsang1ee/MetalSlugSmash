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
#include "BossBackGroundScript.h"
#include "BlockConstructorScript.h"
#include <ysTimer.h>
using namespace ys;

extern ys::Application app;
ys::BossScene::BossScene() : complete(false), completeTime(7.0f)
{
}

ys::BossScene::~BossScene()
{
}

void ys::BossScene::Init()
{
	{
		auto drawBox = object::Instantiate<GameObject>(LayerType::Tool, Vector2(0, 0));
		auto bx = drawBox->AddComponent<CircleCollider2D>();
		bx->SetSize(Vector2::One * 0.1);
		auto ds = drawBox->AddComponent<drawBoxScript>();
	}
	Scene::Init();
}

void ys::BossScene::Update()
{
	Scene::Update();
	if (!boss->IsActive())
	{
		auto as = camera->GetComponent<AudioSource>();
		if(!complete)
		{
			as->Stop();
			as->SetClip(Resources::Find<AudioClip>(L"미션완료"));
			as->SetLoop(false);
			as->Play();
			complete = true;
		}
		else if(completeTime <= 0.0f)
		{
			PostMessage(app.getHWND(), WM_CLOSE, 0, 0);
		}
		else
		{
			completeTime -= Timer::getDeltaTime();
		}
	}
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
	CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::Enemy, true);
	CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::Block, true);
	CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::Wall , true);
	CollisionManager::CollisionLayerCheck(LayerType::PlayerLowerBody, LayerType::EnemyProjectile , true);
	CollisionManager::CollisionLayerCheck(LayerType::Enemy, LayerType::Boom, true);
	CollisionManager::CollisionLayerCheck(LayerType::Enemy, LayerType::Projectile, true);
	CollisionManager::CollisionLayerCheck(LayerType::Block, LayerType::Projectile, true);
	CollisionManager::CollisionLayerCheck(LayerType::Block, LayerType::EnemyProjectile , true);

	player = STAGE1::GetPlayer();
	PlayerLowerBody = STAGE1::GetPlayerLow();
	camera = STAGE1::GetCamera();
	PlayerLowerBody->GetComponent<Transform>()->SetPosition(Vector2(app.getScreenf().x * 9 / 10.0f, 0.0f));

	{
		auto background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(-app.getScreenf().x + 100.0f, 0));
		auto sr = background->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"보스배경"));
		sr->SetSizeByScreen(app.getScreenf() + 2.0f);
		auto bs = background->AddComponent<BossBackGroundScript>();
		bs->SetParallax(100);
	}
	{
		auto background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(100.0f, 0));
		auto sr = background->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"보스배경"));
		sr->SetSizeByScreen(app.getScreenf() + 2.0f);
		auto bs = background->AddComponent<BossBackGroundScript>();
		bs->SetParallax(100);
	}
	{
		auto background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(app.getScreenf().x + 100.0f, 0));
		auto sr = background->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"보스배경"));
		sr->SetSizeByScreen(app.getScreenf() + 2.0f);
		auto bs = background->AddComponent<BossBackGroundScript>();
		bs->SetParallax(100);
	}
	{
		auto blockConstructor = object::Instantiate<GameObject>(LayerType::None);
		auto sc = blockConstructor->AddComponent<BlockConstructorScript>();
		sc->Init();
	}
	//boss
	{
		boss = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
		auto an = boss->AddComponent<Animator>();
		auto rb = boss->AddComponent<RigidBody>();
		rb->SetGravity(Vector2::Zero);
		rb->SetFriction(0.0f);
		auto es = boss->AddComponent<BossScript>();
		auto cd = boss->AddComponent<BoxCollider2D>();

		cd->SetSize(Vector2(7.5f, 7.5f));
		boss->GetComponent<Transform>()->SetPosition(Vector2(200, 250));

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
		an->CrateAnimation(L"보스_죽음", Resources::Find<graphics::Texture>(L"보스_죽음")
			, Vector2(0, 50)
			, Vector2(855, 647)
			, Vector2(0, 0), 12, 0.1f);

		an->PlayAnimation(L"보스_기본_Shoot", true);
	}
	//보스 sfx
	{
		auto bossSfx = object::Instantiate<GameObject>(LayerType::Particle, Vector2(0, 0));
		bossSfx->AddComponent<BossSfxScript>()->SetBoss(boss);

		auto an = bossSfx->AddComponent<Animator>();
		an->CrateAnimation(L"보스_sfx", Resources::Find<graphics::Texture>(L"보스_SFX")
			, Vector2(0, 50)
			, Vector2(825, 374)
			, Vector2(150, -130), 10, 0.1f);

		an->PlayAnimation(L"보스_sfx");
	}
	{
		auto bossSfx = object::Instantiate<GameObject>(LayerType::Particle, Vector2(0, 0));
		bossSfx->AddComponent<BossSfxScript>()->SetBoss(boss);
		auto an = bossSfx->AddComponent<Animator>();
		an->CrateAnimation(L"보스_waves", Resources::Find<graphics::Texture>(L"보스_waves")
			, Vector2(15, 0)
			, Vector2(930, 259)
			, Vector2(-30, 500), 10, 0.1f);
		an->PlayAnimation(L"보스_waves");
	}
	{
		auto bossBullet = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
		auto an = bossBullet->AddComponent<Animator>();
		auto bs = bossBullet->AddComponent<BulletScript>();
		auto cd = bossBullet->AddComponent<BoxCollider2D>();
		cd->SetSize(Vector2(1, 1));
		bossBullet->GetComponent<Transform>()->SetPosition(Vector2(100, 0));

		an->CrateAnimation(L"보스_총알", Resources::Find<graphics::Texture>(L"보스_총알")
			, Vector2(0, 0)
			, Vector2(16, 16)
			, Vector2(0, 0), 1, 0.1f);
		an->PlayAnimation(L"보스_총알", true);


	}
	//플랫폼
	/*{
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
	}*/
	//벽
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
		camera = object::Instantiate<GameObject>(LayerType::Camera);
		renderer::mainCamera = camera->AddComponent<Camera>();
		renderer::mainCamera->SetTarget(PlayerLowerBody);
		camera->GetComponent<Camera>()->SetMinMax(app.getScreenf() / 2.0f, app.getScreenf() / 2.0f);
		camera->AddComponent<CameraScript>();
		auto ad = camera->AddComponent<AudioSource>();
		ad->SetClip(Resources::Find<AudioClip>(L"stage1메인브금"));
		ad->SetLoop(true);
	}
}

void ys::BossScene::OnExit()
{
	for (int i = 0; i < (UINT)LayerType::Max; ++i)
	{
		for (auto& gameObject : Scene::GetLayer((LayerType)i)->GetGameObjects())
		{
			object::Destroy(gameObject);
		}
	}
}
