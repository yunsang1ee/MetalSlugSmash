#pragma once
#include "..\\MyEngine_source\\ysSceneManager.h"
#include "ysPlayScene.h"
#include "ysTitleScene.h"
#include "STAGE1.h"
#include "BossScene.h"
namespace ys
{
	void LoadScenes ()
	{
		//SceneManager::CreateScene<TitleScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<STAGE1>(L"Stage1");
		SceneManager::CreateScene<BossScene>(L"BossScene");
		
		SceneManager::LoadScene(L"Stage1");

	}
}