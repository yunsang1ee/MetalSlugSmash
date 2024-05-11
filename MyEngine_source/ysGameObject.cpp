#include "ysGameObject.h"
#include "ysSceneManager.h"
#include "ysInputManager.h"
#include "ysTimer.h"
#include <iostream>
#include <random>
#include <ysTransform.h>

ys::GameObject::GameObject() 
{
	AddComponnent<Transform>();
}

ys::GameObject::~GameObject()
{
}

void ys::GameObject::Init()
{
	for (auto component : components)
		component->Init();
}

void ys::GameObject::Update()
{
	for (auto component : components)
		component->Update();
}

void ys::GameObject::LateUpdate()
{
	for (auto component : components)
		component->LateUpdate();
}

void ys::GameObject::Render(HDC hDC)
{
	for (auto component : components)
		component->Render(hDC);
	
}