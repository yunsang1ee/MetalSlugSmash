#pragma once
#include "CommonInclude.h"
#include "ysScene.h"
namespace ys
{
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name);

		static Scene* LoadScene(const std::wstring& name);

		static Scene* GetaActiveScene() { return activeScene; }

		static void Init();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hDc);

	private:
		static std::map<std::wstring, Scene*> Scenes;
		static Scene* activeScene;
	};
}

