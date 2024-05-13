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
		{
			backBackground = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, 600));
			auto tr = backBackground->GetComponent<Transform>();
			tr->setName(L"TRBackBack");

			auto sr = backBackground->AddComponnent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"배경의배경"));
			sr->setName(L"SRBackBack");
		}
		{
			background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, 300));
			auto tr = background->GetComponent<Transform>();
			tr->setName(L"TRBack");

			auto sr = background->AddComponnent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<graphics::Texture>(L"배경"));
			sr->setName(L"SRBack");
		}

		{
			player = object::Instantiate<Player>(LayerType::Player, { app.getScreen().x / 5.0f, app.getScreen().y * 3 / 5.0f });
			auto sr = player->AddComponnent<SpriteRenderer>();

			sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어가만"));
			sr->setName(L"SR");
			/*player = new Player();
			auto tr = player->AddComponnent<Transform>();
			tr->SetPosition({ std::fmodf(uid(random), (60 * 16)), 500 });
			tr->setName(L"TR");

			auto sr = player->AddComponnent<SpriteRenderer>();
			sr->setName(L"SR");
			sr->ImageLoad(L"C:\\Users\\user\\source\\repos\\WinProgramming\\Resource\\플레이어가만.bmp");
			AddGameObject(player, LayerType::Player);*/
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
		tr->SetPosition(Vector2(0, 600));
		tr = background->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, 300));
		tr = player->GetComponent<Transform>();
		tr->SetPosition({ app.getScreen().x / 5.0f, app.getScreen().y * 3 / 5.0f });
	}
	void PlayScene::OnExit()
	{
		auto tr = backBackground->GetComponent<Transform>();
		tr->SetPosition(Vector2::Zero);
		tr = background->GetComponent<Transform>();
		tr->SetPosition(Vector2::Zero);
		tr = player->GetComponent<Transform>();
		std::random_device rd;
		std::mt19937 random(rd());
		std::uniform_real_distribution<> uid;
		tr->SetPosition({ std::fmodf(uid(random), (60 * 16)), 500 });
	}
}