#pragma once

namespace ys::enums
{
	enum class LayerType
	{
		None,
		BackGround,
		Projectile,
		Enemy,
		Player,
		Particle,
		Camera,
		Max = 16
	};

	enum class ResourceType
	{
		Texture,
		AudioClip,
		Prefab,
		End
	};

	enum class ComponentType
	{
		Transform, 
		Collider,
		Script,
		SpriteRenderer,
		//Animator,
		Camera,
		End
	};// Reference : Unity lifeCycle
}