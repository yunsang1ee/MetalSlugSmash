#include "ysPlayScene.h"
#include "ysPlayer.h"
#include <random>
#include <ysTransform.h>
#include <ysSpriteRenderer.h>
#include "ysTitleScene.h"
#include "ysInputManager.h"
#include "ysSceneManager.h"
#include "ysObject.h"
#include "ysTexture.h"

namespace ys
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Init()
	{
		{
			backBackground = new GameObject();
			auto tr = backBackground->AddComponnent<Transform>();
			tr->SetPosition(Vector2::Zero);
			tr->setName(L"TRBackBack");
			auto sr = backBackground->AddComponnent<SpriteRenderer>();

			graphics::Texture* tex = new graphics::Texture();
			tex->Load(L"..\\Resource\\배경의배경.bmp");

			sr->setName(L"SRBackBack");
			AddGameObject(backBackground, LayerType::BackGround);
		}
		{
			background = new GameObject();
			auto tr = background->AddComponnent<Transform>();
			tr->SetPosition(Vector2::Zero);
			tr->setName(L"TRBack");
			auto sr = background->AddComponnent<SpriteRenderer>();

			graphics::Texture* tex = new graphics::Texture();
			tex->Load(L"..\\Resource\\배경.bmp");

			sr->setName(L"SRBack");
			AddGameObject(background, LayerType::BackGround);

		}

		{
			std::random_device rd;
			std::mt19937 random(rd());
			std::uniform_int_distribution<> uid;
			player = object::Instantiate<Player>(LayerType::Player, { std::fmodf(uid(random), (60 * 16)), 500 });
			auto sr = player->AddComponnent<SpriteRenderer>();

			graphics::Texture* tex = new graphics::Texture();
			tex->Load(L"..\\Resource\\플레이어가만.bmp");

			sr->setName(L"SR");
			AddGameObject(player, LayerType::Player);
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
		tr->SetPosition(Vector2::Zero);
		tr = background->GetComponent<Transform>();
		tr->SetPosition(Vector2::Zero);
		tr = player->GetComponent<Transform>();
		std::random_device rd;
		std::mt19937 random(rd());
		std::uniform_int_distribution<> uid;
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
		std::uniform_int_distribution<> uid;
		tr->SetPosition({ std::fmodf(uid(random), (60 * 16)), 500 });
	}
}