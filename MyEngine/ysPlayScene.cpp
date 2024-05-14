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
		//Camera
		{
			auto camera = object::Instantiate<GameObject>(LayerType::None);
			auto cameraComp = camera->AddComponnent<Camera>();
			cameraComp->SetTarget(player);
			renderer::mainCamera = cameraComp;

			camera->AddComponnent<PlayerScript>();
		}
		//backGrounds
		{
			backBackground = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, -600));

			auto sr = backBackground->AddComponnent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"배경의배경"));

			auto bs = backBackground->AddComponnent<BackGroundScript>();
			bs->SetParallax(200);
		}
		{
			background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, -300));

			auto sr = background->AddComponnent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"배경"));

			auto bs = background->AddComponnent<BackGroundScript>();
			bs->SetParallax(400);
		}
		//Player
		{
			player = object::Instantiate<Player>(LayerType::Player, { app.getScreen().x / 5.0f, app.getScreen().y * 3 / 5.0f });
			auto sr = player->AddComponnent<SpriteRenderer>();

			sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어가만"));
			sr->setName(L"SR");

			player->AddComponnent<PlayerScript>();
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
		tr->SetPosition({ app.getScreen().x / 5.0f, app.getScreen().y * 3 / 5.0f });
	}
	void PlayScene::OnExit()
	{
		auto tr = backBackground->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, -300));
		tr = background->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, -200));
		tr = player->GetComponent<Transform>();
		tr->SetPosition({ app.getScreen().x / 5.0f, app.getScreen().y * 3 / 5.0f });
	}
}