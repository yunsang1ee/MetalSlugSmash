#include "ysPlayScene.h"
#include "ysPlayer.h"
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

extern ys::Application app;

namespace ys
{
	PlayScene::PlayScene() : backBackground(nullptr), background(nullptr), player(nullptr)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Init()
	{
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(LayerType::Enemy, LayerType::Projectile, true);
		//backGrounds
		{
			backBackground = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, -600));

			auto sr = backBackground->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"배경의배경"));

			auto bs = backBackground->AddComponent<BackGroundScript>();
			bs->SetParallax(-100);
		}
		{
			background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, -300));

			auto sr = background->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"배경"));

			auto bs = background->AddComponent<BackGroundScript>();
			bs->SetParallax(100);
		}
		//Player
		{
			player = object::Instantiate<Player>(LayerType::Player, { app.getScreen().x / 2.0f, app.getScreen().y * 4 / 10.0f });
			
			auto sr = player->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어가만"));

			player->AddComponent<PlayerScript>();
			auto cd = player->AddComponent<CircleCollider2D>();
			cd->SetOffset(Vector2(20, 30));
		}
		//Enemy
		{
			auto enemy = object::Instantiate<Player>(LayerType::Enemy, { app.getScreenf().x, app.getScreen().y * 4 / 10.0f });
			
			auto sr = enemy->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어가만"));

			enemy->AddComponent<EnemyScript>();
			auto cd = enemy->AddComponent<CircleCollider2D>();
			cd->SetOffset(Vector2(20, 30));
		}
		//Camera
		{
			auto camera = object::Instantiate<GameObject>(LayerType::Camera);
			renderer::mainCamera = camera->AddComponent<Camera>();
			renderer::mainCamera->SetTarget(player);

		}
		Scene::Init();
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
		if (ys::InputManager::getKeyDown((UINT)ys::Key::N))
			ys::SceneManager::LoadScene(L"TitleScene");
	}
	void PlayScene::Render(HDC hDc)
	{
		Scene::Render(hDc);
	}
	void PlayScene::OnEnter()
	{
		auto tr = backBackground->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, -300));
		tr = background->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, -200));
		tr = player->GetComponent<Transform>();
		tr->SetPosition({ app.getScreen().x / 2.0f, app.getScreen().y * 0.49f });
	}
	void PlayScene::OnExit()
	{
		auto tr = backBackground->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, -300));
		tr = background->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, -200));
		tr = player->GetComponent<Transform>();
		tr->SetPosition({ app.getScreen().x / 2.0f, app.getScreen().y * 0.49f });
	}
}