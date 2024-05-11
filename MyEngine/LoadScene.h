#pragma once
#include "..\\MyEngine_source\\ysSceneManager.h"
#include "..\\MyEngine_source\\ysSceneManager.cpp"
#include "ysPlayScene.h"
#include "ysTitleScene.h"

namespace ys
{
	void LoadScenes ()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<EndScene>(L"EndScene");

		SceneManager::LoadScene(L"TitleScene");

	}
}