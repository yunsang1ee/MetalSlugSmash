#include "ysLayer.h"
#include "ysGameObject.h"

namespace ys
{
	Layer::Layer() : objects{}
	{
	}

	Layer::~Layer()
	{
		for (auto object : objects)
		{
			delete object;
			object = nullptr;
		}
	}

	void Layer::Init()
	{
		for (auto object : objects)
		{
			if (object == nullptr) continue;
			object->Init();
		}
	}
	void Layer::Update()
	{
		for (GameObject* object : objects)
		{
			if (object == nullptr) continue;

			if (object->GetState() == GameObject::State::Active)
				object->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (auto object : objects)
		{
			if (object == nullptr) continue;

			if (object->GetState() == GameObject::State::Active)
				object->LateUpdate();
		}
	}
	void Layer::Render(HDC hDC)
	{
		for (auto object : objects)
		{
			if (object == nullptr) continue;

			if (object->GetState() == GameObject::State::Active)
				object->Render(hDC);
		}
	}

	void Layer::Destroy()
	{
		for (auto iter = objects.begin(); iter != objects.end();)
		{
			if (*iter == nullptr) continue;
			auto state = (*iter)->GetState();
			if (state == GameObject::State::Dead)
			{
				auto deleteObj = *iter;
				iter = objects.erase(iter);
				delete deleteObj; deleteObj = nullptr;
			}
			else
				++iter;
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr) return;
		objects.push_back(gameObject);
	}
}