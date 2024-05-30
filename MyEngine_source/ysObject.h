#pragma once
#include <ysComponent.h>
#include <ysGameObject.h>
#include <ysLayer.h>
#include <ysSceneManager.h>
#include <ysScene.h>
#include <ysTransform.h>

namespace ys::object
{  
	template <typename T>
	static T* Instantiate(const enums::LayerType& type)
	{
		T* gameObject = new T();
		auto activeScene = SceneManager::GetActiveScene(); //���� ��Ƽ�����
		auto layer = activeScene->GetLayer(type); //�ش��ϴ� ���̾
		gameObject->SetLayerType(type);
		layer->AddGameObject(gameObject); //������Ʈ�� �߰��Ѵ�
		return gameObject;
	}

	template <typename T>
	static T* Instantiate(const enums::LayerType& type, const Vector2& position)
	{
		T* gameObject = new T();
		auto activeScene = SceneManager::GetActiveScene(); //���� ��Ƽ�����
		auto layer = activeScene->GetLayer(type); //�ش��ϴ� ���̾
		gameObject->SetLayerType(type);
		layer->AddGameObject(gameObject); //������Ʈ�� �߰��Ѵ�

		auto tr = gameObject->GetComponent<Transform>();
		tr->SetPosition(position);

		return gameObject;
	}
	template <typename T>
	static T* Instantiate(const enums::LayerType& type, const Vector2& position, const Vector2& rotation)
	{
		T* gameObject = new T();
		auto activeScene = SceneManager::GetActiveScene(); //���� ��Ƽ�����
		auto layer = activeScene->GetLayer(type); //�ش��ϴ� ���̾
		gameObject->SetLayerType(type);
		layer->AddGameObject(gameObject); //������Ʈ�� �߰��Ѵ�

		auto tr = gameObject->GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);

		return gameObject;
	}

	static void DontDestroyOnLoad(GameObject* gameObject)
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		activeScene->EraseGameObject(gameObject);
		SceneManager::GetAbsoluteScene()->AddGameObject(gameObject, gameObject->GetLayerType());
	}

	static void Destroy(GameObject* object) { if(object != nullptr) object->death(); }
}