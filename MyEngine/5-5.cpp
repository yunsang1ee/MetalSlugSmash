#include "5-5.h"
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
#include "ysPlayer.h"
#include "CameraScript.h"
#include "BlockScript.h"
#include "pracPlayerScript.h"
#include <ysAnimation.h>

extern ys::Application app;
using namespace ys;

prac::prac()
{
}

prac::~prac()
{
}

void prac::Init()
{
	CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Enemy, true);
	CollisionManager::CollisionLayerCheck(LayerType::Enemy, LayerType::Projectile, true);
	CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Block, true);
	{
		player = object::Instantiate<GameObject>(LayerType::Player, Vector2(-10, -10));
		auto sr = player->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"플레이어가만"));
		auto tr = player->AddComponent<Transform>();
		
		player->AddComponent<pracPlayerScript>();
		player->AddComponent<BoxCollider2D>()->SetOffset(Vector2(20, 30));
		auto an = player->AddComponent<Animation>();
		an->CrateAnimation(L"플레이어이동좌이동", 0, 1, 0.1f);

	}
	{
		Blocks.push_back(object::Instantiate<GameObject>(LayerType::Block, Vector2(0, 0)));
		auto sr = Blocks[0]->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"Block"));
	}
	{
		auto enemy = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
		auto sr = enemy->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"게1"));
		enemy->AddComponent<EnemyScript>();
		enemy->AddComponent<BoxCollider2D>()->SetOffset(Vector2(20, 30));
		
	}
	{
		auto enemy = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(200, 0));
		auto sr = enemy->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"게1"));
		enemy->AddComponent<EnemyScript>();
		enemy->AddComponent<BoxCollider2D>()->SetOffset(Vector2(20, 30));
		
	}
	{
		auto enemy = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(-200, 0));
		auto sr = enemy->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"게1"));
		enemy->AddComponent<EnemyScript>();
		enemy->AddComponent<BoxCollider2D>()->SetOffset(Vector2(20, 30));

	}

	{
		camera = object::Instantiate<GameObject>(LayerType::Camera);
		renderer::mainCamera = camera->AddComponent<Camera>();
		renderer::mainCamera->SetTarget(player);
		camera->GetComponent<Camera>()->SetMinMax(Vector2(0, 0), Vector2(0,0));
		camera->AddComponent<CameraScript>();
	}
	Scene::Init();
}

void prac::Update()
{
	Scene::Update();
}

void prac::LateUpdate()
{
	Scene::LateUpdate();
}

void prac::Render(HDC hDC)
{
	Scene::Render(hDC);
}


