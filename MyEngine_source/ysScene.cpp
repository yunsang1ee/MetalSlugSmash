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
		for (auto layer : layers)
		{
			delete layer;
			layer = nullptr;
		}
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

	void Scene::Destroy()
	{
		for (auto layer : layers)
		{
			if (layer == nullptr) continue;
			layer->Destroy();
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
		layers[static_cast<UINT>(type)]->setType(type);
	}
}