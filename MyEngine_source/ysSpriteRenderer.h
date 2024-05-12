#pragma once
#include "ysComponent.h"
#include "ysTexture.h"

namespace ys
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Init() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hDC) override;

		void SetTexture(graphics::Texture* texture) { this->texture = texture; }
		void SetSize(math::Vector2 size) { this->size = size; }

	private:
		graphics::Texture* texture;
		math::Vector2 size;
	};
}