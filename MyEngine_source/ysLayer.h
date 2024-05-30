#pragma once
#include "ysEntity.h"
#include "ysComponent.h"

namespace ys
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hDC);
		virtual void Destroy();
		
		void AddGameObject(GameObject* gameObject);
		void EraseGameObject(GameObject* gameObject);
		const std::vector<GameObject*> GetGameObjects() const { return objects; }

	private:
		//LayerType type;
		std::vector<GameObject*> objects;
	}; 
}

