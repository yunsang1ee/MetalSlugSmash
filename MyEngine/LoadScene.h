#pragma once
#include "..\\MyEngine_source\\ysSceneManager.h"
#include "..\\MyEngine_source\\ysSceneManager.cpp"
#include "ysPlayScene.h"
#include "ysTitleScene.h"
#include"STAGE1.h"
#include"5-5.h"
namespace ys
{
	void LoadScenes ()
	{
		//SceneManager::CreateScene<TitleScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<EndScene>(L"EndScene");
		//SceneManager::CreateScene<STAGE1>(L"Stage1");
		//SceneManager::LoadScene(L"Stage1");
		SceneManager::CreateScene<prac>(L"prac");

		SceneManager::LoadScene(L"prac");
	}
}