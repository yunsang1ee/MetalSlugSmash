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
		SpriteRenderer,
		Script,
		Camera,
		End
	};// Transform -> Script -> Renderer
}