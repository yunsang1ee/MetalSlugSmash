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
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(LayerType::Enemy, LayerType::Projectile, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Block, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::BackGround, true);
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
			sr->SetSizeByScreen(Vector2(sr->GetTexture()->GetWidth() * 4.5f, sr->GetTexture()->GetHeight() * 4.5f));
			auto bx1 =background->AddComponent<BoxCollider2D>();
			bx1->SetOffset(Vector2(0, (sr->GetTexture()->GetHeight() * 4.5f)-230));
			bx1->SetSize(Vector2(31, 0.1f));
			bx1->setName(L"BackGround");
			auto bs = background->AddComponent<BackGroundScript>();
			bs->SetParallax(100);
		}
		//Player
		{
			player = object::Instantiate<Player>(LayerType::Player, { app.getScreen().x / 2.0f, app.getScreen().y * 4 / 10.0f });

			auto sr = player->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어가만"));
			auto plysc =player->AddComponent<PlayerScript>();
			plysc->SetSpeed(500.f);
			auto cd = player->AddComponent<CircleCollider2D>();
			cd->SetOffset(Vector2(20, 30));
			//콜라이더 만들면 스크립만들어야함 -> 콜리전 매니져에서 스크립트로 전달
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
			Blocks[Blocks.size()-1] = object::Instantiate<GameObject>(LayerType::Block, {1640, 695});
			auto block = Blocks[Blocks.size() - 1];
			
			block->AddComponent<BoxCollider2D>();
			block->GetComponent<BoxCollider2D>()->setName(L"Block");
			block->AddComponent<BlockScript>();

		}
		//block2
		{
			Blocks.resize(Blocks.size() + 1);
			Blocks[Blocks.size() - 1] = object::Instantiate<GameObject>(LayerType::Block, { 0, app.getScreen().y-100.f});
			auto block = Blocks[Blocks.size() - 1];
			
			auto bx=block->AddComponent<BoxCollider2D>();
			bx->setName(L"BackGround");
			bx->SetSize(Vector2(31, 0.1f));
			block->AddComponent<BlockScript>();

		}
		//Camera
		{
			camera = object::Instantiate<GameObject>(LayerType::Camera);
			renderer::mainCamera = camera->AddComponent<Camera>();
			renderer::mainCamera->SetTarget(player);
			camera->GetComponent<Camera>()->SetMinMax(Vector2(650, 420), Vector2(2405, 363));
			camera->AddComponent<CameraScript>();
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

	void ys::STAGE1::Render(HDC hDC)
	{
		Scene::Render(hDC);
	}

}
