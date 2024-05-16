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
		}
		//Bullet
		{
			auto bullet = object::Instantiate<GameObject>(LayerType::Projectile, { app.getScreen().x / 2.0f, app.getScreen().y * 4 / 10.0f });
			
			auto sr = bullet->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"총알"));

			bullet->AddComponent<BulletScript>();
			bulletPool.assign(100, bullet);
		}
		//Camera
		{
			camera = object::Instantiate<GameObject>(LayerType::Camera);
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