#include "ysSceneManager.h"

namespace ys
{
	std::map<std::wstring, Scene*> SceneManager::Scenes;
	Scene* SceneManager::activeScene;

	template<typename T>
	Scene* SceneManager::CreateScene(const std::wstring& name)
	{
		T* scene = new T();
		scene->setName(name);
		activeScene = scene;
		scene->Init();

		Scenes.insert(std::make_pair(name, scene));
		return scene;
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		if (activeScene)
			activeScene->OnExit();
		auto iter = Scenes.find(name);
		if (iter == Scenes.end())
			return nullptr;

		activeScene = iter->second;
		activeScene->OnEnter();
		return activeScene;
	}

	void SceneManager::Init()
	{
		activeScene->Init();
	}
	void SceneManager::Update()
	{
		activeScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		activeScene->LateUpdate();
	}
	void SceneManager::Render(HDC hDc)
	{
		activeScene->Render(hDc);
	}
}