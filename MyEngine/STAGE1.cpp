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
		//backGrounds
		{
			backBackground = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(30, -400));

			auto sr = backBackground->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"����ǹ��"));
			
			auto bs = backBackground->AddComponent<BackGroundScript>();
			bs->SetParallax(-100);
		}
		{
			background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, -300));

			auto sr = background->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"���"));

			auto bs = background->AddComponent<BackGroundScript>();
			bs->SetParallax(100);
		}
		//Player
		{
			player = object::Instantiate<Player>(LayerType::Player, { app.getScreen().x / 2.0f, app.getScreen().y * 4 / 10.0f });

			auto sr = player->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��"));
			//Ű �޾ƿͼ� �÷��̾� �׸� �ٲ�ߵ�
			//Ű ��� �޾ƿ�?
			if (ys::InputManager::getKeyDown((UINT)ys::Key::W)) {
				sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��̵�"));
			}
				
			

			player->AddComponent<PlayerScript>();
			auto cd = player->AddComponent<CircleCollider2D>();
			cd->SetOffset(Vector2(20, 30));
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
		//Camera
		{
			auto camera = object::Instantiate<GameObject>(LayerType::Camera);
			renderer::mainCamera = camera->AddComponent<Camera>();
			renderer::mainCamera->SetTarget(player);

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

	void ys::STAGE1::Render(HDC hDC)
	{
		Scene::Render(hDC);
	}

}
