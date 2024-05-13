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

		math::Vector2 GetSize() { return size; }

		graphics::Texture* GetTexture() { return texture; }

		void SetTexture(graphics::Texture* texture) { this->texture = texture; }
		void SetSizeByTexture(math::Vector2 size) { this->size = size; }
		void SetSizeByScreen(math::Vector2 size)
		{
			this->size.x = size.x / texture->GetWidth();
			this->size.y = size.y / texture->GetHeight();
		}

	private:
		graphics::Texture* texture;
		math::Vector2 size;
	};
}