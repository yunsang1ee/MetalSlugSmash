#include "ysTitleScene.h"
#include <ysTransform.h>
#include <ysSpriteRenderer.h>
#include "ysPlayer.h"
#include "ysPlayScene.h"
#include "ysInputManager.h"
#include "ysSceneManager.h"
#include "ysResources.h"
#include "ysTexture.h"

ys::TitleScene::TitleScene()
{
}

ys::TitleScene::~TitleScene()
{
}

void ys::TitleScene::Init()
{
	{
		Player* background = new Player();
		auto tr = background->GetComponent<Transform>();
		tr->SetPosition(Vector2::Zero);
		tr->setName(L"TRTilte");
		auto sr = background->AddComponent<SpriteRenderer>();

		sr->SetTexture(Resources::Find<graphics::Texture>(L"CloudOcean"));
		sr->setName(L"SRTilte1");
		AddGameObject(background, ys::enums::LayerType::BackGround);
	}
	{
		Player* background = new Player();
		auto tr = background->GetComponent<Transform>();
		tr->SetPosition({16 * 100, 0});
		tr->setName(L"TRTilte");
		auto sr = background->AddComponent<SpriteRenderer>();
		
		sr->SetTexture(Resources::Find<graphics::Texture>(L"CloudOcean"));
		sr->setName(L"SRTilte2");
		AddGameObject(background, ys::enums::LayerType::BackGround);
	}
	Scene::Init();
}

void ys::TitleScene::Update()
{
	Scene::Update();
}

void ys::TitleScene::LateUpdate()
{
	Scene::LateUpdate();
	if (ys::InputManager::getKeyDown((UINT)ys::Key::N))
		ys::SceneManager::LoadScene(L"PlayScene");
}

void ys::TitleScene::Render(HDC hDC, const int& index)
{
	Scene::Render(hDC, index);
}
