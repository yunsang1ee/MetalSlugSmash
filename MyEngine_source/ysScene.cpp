#include "ysScene.h"
#include <algorithm>
namespace ys
{
	Scene::Scene()
	{
		layers.resize(static_cast<UINT>(LayerType::Max));
		std::for_each(layers.begin(), layers.end(), [](Layer*& layer)
			{
				layer = new Layer();
			});
	}
	Scene::~Scene()
	{
	}

	void Scene::Init()
	{
		for (auto layer : layers)
		{
			if (layer == nullptr) continue;
			layer->Init();
		}
	}
	void Scene::Update()
	{
		for (auto layer : layers)
		{
			if (layer == nullptr) continue;
			layer->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (auto layer : layers)
		{
			if (layer == nullptr) continue;
			layer->LateUpdate();
		}
	}
	void Scene::Render(HDC hDC)
	{
		for (auto layer : layers)
		{
			if (layer == nullptr) continue;
			layer->Render(hDC);
		}
	}

	void Scene::OnEnter()
	{
	}

	void Scene::OnExit()
	{
	}

	void Scene::AddGameObject(GameObject* gameObject, const enums::LayerType& type)
	{
		layers[static_cast<UINT>(type)]->AddGameObject(gameObject);
	}
}