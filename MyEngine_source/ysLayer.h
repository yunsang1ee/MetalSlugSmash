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
		
		void AddGameObject(GameObject* gameObject);

	private:
		//LayerType type;
		std::vector<GameObject*> objects;
	}; 
}

