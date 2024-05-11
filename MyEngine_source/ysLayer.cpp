#include "ysLayer.h"
#include "ysGameObject.h"

namespace ys
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Init()
	{
		for (auto& object : objects)
		{
			if (object == nullptr) continue;
			object->Init();
		}
	}
	void Layer::Update()
	{
		for (auto& object : objects)
		{
			if (object == nullptr) continue;
			object->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (auto& object : objects)
		{
			if (object == nullptr) continue;
			object->LateUpdate();
		}
	}
	void Layer::Render(HDC hDC)
	{
		for (auto& object : objects)
		{
			if (object == nullptr) continue;
			object->Render(hDC);
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr) return;
		objects.push_back(gameObject);
	}
}