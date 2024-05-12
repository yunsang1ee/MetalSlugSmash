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
#include "ysTexture.h"

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
			backBackground = new GameObject();
			auto tr = backBackground->GetComponent<Transform>();
			tr->setName(L"TRBackBack");
			auto sr = backBackground->AddComponnent<SpriteRenderer>();

			sr->SetTexture(Resources::Find<graphics::Texture>(L"����ǹ��"));
			sr->setName(L"SRBackBack");
			AddGameObject(backBackground, LayerType::BackGround);
		}
		{
			background = new GameObject();
			auto tr = backBackground->GetComponent<Transform>();
			tr->setName(L"TRBack");
			auto sr = background->AddComponnent<SpriteRenderer>();

			sr->SetTexture(Resources::Find<graphics::Texture>(L"���"));
			sr->setName(L"SRBack");
			AddGameObject(background, LayerType::BackGround);
		}

		{
			std::random_device rd;
			std::mt19937 random(rd());
			std::uniform_real_distribution<> uid;
			player = object::Instantiate<Player>(LayerType::Player, { std::fmodf(uid(random), (60 * 16)), 500 });
			auto sr = player->AddComponnent<SpriteRenderer>();

			sr->SetTexture(Resources::Find<graphics::Texture>(L"�÷��̾��"));
			sr->setName(L"SR");
			AddGameObject(player, LayerType::Player);
			/*player = new Player();
			auto tr = player->AddComponnent<Transform>();
			tr->SetPosition({ std::fmodf(uid(random), (60 * 16)), 500 });
			tr->setName(L"TR");

			auto sr = player->AddComponnent<SpriteRenderer>();
			sr->setName(L"SR");
			sr->ImageLoad(L"C:\\Users\\user\\source\\repos\\WinProgramming\\Resource\\�÷��̾��.bmp");
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
		tr->SetPosition(Vector2::Zero);
		tr = background->GetComponent<Transform>();
		tr->SetPosition(Vector2::Zero);
		tr = player->GetComponent<Transform>();
		std::random_device rd;
		std::mt19937 random(rd());
		std::uniform_real_distribution<> uid;
		tr->SetPosition({ std::fmodf(uid(random), (60 * 16)), 500 });
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