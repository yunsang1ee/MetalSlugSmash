#include "BlockScript.h"
#include<ysGameObject.h>
#include<ysBoxCollider2D.h>
#include<ysSceneManager.h>
#include<ysScene.h>
using namespace ys;
BlockScript::BlockScript()
{
}

BlockScript::~BlockScript()
{
}

void BlockScript::Init()
{
	//GetOwner()->GetComponent<BoxCollider2D>()->setName(L"Block");
	
}

void BlockScript::Update()
{
	auto scene = dynamic_cast<Scene*>(SceneManager::GetaActiveScene());
	auto plyr = scene->GetLayer(LayerType::Player)->GetGameObjects()[0];
	int a = 0;
}

void BlockScript::LateUpdate()
{
}

void BlockScript::Render(HDC hDC)
{
}

void BlockScript::OnCollisionEnter(Collider* other)
{
	
}

void BlockScript::OnCollisionStay(Collider* other)
{
}

void BlockScript::OnCollisionExit(Collider* other)
{
}
