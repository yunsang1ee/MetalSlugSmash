#pragma once
#include "CommonInclude.h"
#include "ysComponent.h"
using namespace ys::math;
using namespace ys::enums;

namespace ys 
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hDC);
		
		template <typename T>
		T* AddComponnent()
		{
			T* comp = new T();
			comp->SetOwner(this);
			components.at(static_cast<UINT>(comp->GetType())) = comp;
			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* comp = nullptr;
			for(auto component : components)
			{
				comp = dynamic_cast<T*>(component);
				if (comp) break;
			}
			return  comp;
		}

	private:
		std::vector<Component*> components;
	};
}