#include "BossScene.h"
#include "ysGameObject.h"
#include "STAGE1.h"
#include <random>
#include <fstream>
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
#include"drawBoxScript.h"
#include"ysAnimation.h"
#include"ysAnimator.h"
#include "PlayerLowerBodyScript.h"
#include <ysRigidBody.h>
#include "ysSoundManager.h"
#include <ysAudioListener.h>
#include <ysAudioSource.h>
using namespace ys;

ys::BossScene::BossScene()
{
}

ys::BossScene::~BossScene()
{
}

void ys::BossScene::Init()
{
	{
		auto background = object::Instantiate<GameObject>(LayerType::BackGround, Vector2(0, 0));
		auto sr = background->AddComponent<SpriteRenderer>();
		sr->SetTexture(Resources::Find<graphics::Texture>(L"�������"));
		auto bs = background->AddComponent<BackGroundScript>();
	}
	//boss
	{
		auto boss = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
		auto an = boss->AddComponent<Animator>();
		auto es = boss->AddComponent<EnemyScript>();
		auto cd = boss->AddComponent<BoxCollider2D>();
		boss->GetComponent<Transform>()->SetPosition(Vector2(100, 0));

		an->CrateAnimation(L"����_�⺻_Move", Resources::Find<graphics::Texture>(L"����_�⺻_Move")
			, Vector2(0, 49)
			, Vector2(842, 707)
			, Vector2(0, 0), 12, 0.1f);
		an->CrateAnimation(L"����_�⺻_Shoot", Resources::Find<graphics::Texture>(L"����_�⺻_Shoot")
			, Vector2(0, 49)
			, Vector2(855, 707)
			, Vector2(0, 0), 12, 0.1f);
		an->CrateAnimation(L"����_Cannon_Depoly", Resources::Find<graphics::Texture>(L"����_Cannon_Depoly")
			, Vector2(0, 50)
			, Vector2(855, 727)
			, Vector2(0, 0), 12, 0.1f);
		an->CrateAnimation(L"����_Cannon_Move", Resources::Find<graphics::Texture>(L"����_Cannon_Move")
			, Vector2(0, 50)
			, Vector2(855, 727)
			, Vector2(0, 0), 12, 0.1f);

		an->CrateAnimation(L"����_Cannon_Shoot", Resources::Find<graphics::Texture>(L"����_Cannon_Shoot")
			, Vector2(0, 50)
			, Vector2(855, 727)
			, Vector2(0, 0), 12, 0.1f);
		an->CrateAnimation(L"����_����", Resources::Find<graphics::Texture>(L"����_����")
			, Vector2(0, 50)
			, Vector2(855, 647)
			, Vector2(0, 0), 12, 0.1f);

		an->PlayAnimation(L"����_�⺻_Shoot", true);
	}
	//���� sfx
	{
		auto bossSfx = object::Instantiate<GameObject>(LayerType::Enemy, Vector2(0, 0));
		//���� ��ġ�� ���缭 ����������
		bossSfx->GetComponent<Transform>()->SetPosition(Vector2(5500, 0));
		auto an = bossSfx->AddComponent<Animator>();
		an->CrateAnimation(L"����_sfx", Resources::Find<graphics::Texture>(L"����_SFX")
			, Vector2(0, 50)
			, Vector2(825, 374)
			, Vector2(0, 0), 10, 0.1f);
		an->PlayAnimation(L"����_sfx");
	}
	

	Scene::Init();
}

void ys::BossScene::Update()
{
	Scene::Update();
}

void ys::BossScene::LateUpdate()
{
	Scene::LateUpdate();
}

void ys::BossScene::Render(HDC hDC, const int& index)
{
	Scene::Render(hDC,index);
}

void ys::BossScene::Destroy()
{
	Scene::Destroy();
}

void ys::BossScene::OnEnter()
{
}

void ys::BossScene::OnExit()
{
}
