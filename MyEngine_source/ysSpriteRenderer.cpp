#include "ysSpriteRenderer.h"
#include "ysGameObject.h"
#include "ysTransform.h"
#include "ysTexture.h"
#include <cassert>

ys::SpriteRenderer::SpriteRenderer()
	: Component(enums::ComponentType::SpriteRenderer), texture(nullptr), size (Vector2::One)
{
}

ys::SpriteRenderer::~SpriteRenderer()
{
}

void ys::SpriteRenderer::Init()
{
}

void ys::SpriteRenderer::Update()
{
}

void ys::SpriteRenderer::LateUpdate()
{
}

void ys::SpriteRenderer::Render(HDC hDC)
{
	if (texture == nullptr) 
		assert(false, L"File error!");
	auto tr = GetOwner()->GetComponent<Transform>();
	auto position = tr->GetPosition();

	if (texture->GetTextureType() == graphics::Texture::TextureType::Bmp)
	{
		assert(TransparentBlt(hDC, position.x, position.y, texture->GetWidth(), texture->GetHeight()
			, texture->GetDC(), 0, 0, texture->GetWidth(), texture->GetHeight(), RGB(255, 0, 255)));
	}
	else if (texture->GetTextureType() == graphics::Texture::TextureType::Png)
	{
		Gdiplus::Graphics graphics(hDC);
		Gdiplus::ImageAttributes imageAttr;
		imageAttr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255));
		const auto& name = getName();
		if (name == L"SRBackBack")
		{
			graphics.DrawImage(texture->GetImage(), Gdiplus::Rect(0, 0, 4 * 300, 3 * 300)
				, position.x, position.y + 400, 4 * 300, 3 * 250, Gdiplus::UnitPixel, &imageAttr);
		}
		else if (name == L"SRBack")
		{
			graphics.DrawImage(texture->GetImage(), Gdiplus::Rect(0, 0, 4 * 300, 3 * 300)
				, position.x, position.y + 300, 4 * 300, 3 * 250, Gdiplus::UnitPixel, &imageAttr);
		}
		else if (name == L"SR")
		{
			graphics.DrawImage(texture->GetImage(), Gdiplus::Rect(position.x, position.y, texture->GetWidth(), texture->GetHeight())
				, 0, 0, texture->GetWidth(), texture->GetHeight(), Gdiplus::UnitPixel, &imageAttr);
		}
		else if (name == L"SRTilte1")
		{
			graphics.DrawImage(texture->GetImage(), Gdiplus::Rect(position.x, position.y, texture->GetWidth(), texture->GetHeight())
				, 0, 0, texture->GetWidth(), texture->GetHeight() / 2, Gdiplus::UnitPixel, &imageAttr);
			if (-position.x > texture->GetWidth())
				tr->SetPosition({ static_cast<float>(texture->GetWidth()), 0 });
		}
		else if (name == L"SRTilte2")
		{
			graphics.DrawImage(texture->GetImage(), Gdiplus::Rect(position.x, position.y, texture->GetWidth(), texture->GetHeight())
				, 0, texture->GetHeight() / 2, texture->GetWidth(), texture->GetHeight() / 2, Gdiplus::UnitPixel, &imageAttr);
			if (-position.x > texture->GetWidth())
				tr->SetPosition({ static_cast<float>(texture->GetWidth()), 0 });
		}
		else
		{
			graphics.DrawImage(texture->GetImage()
				, Gdiplus::Rect(position.x, position.y, texture->GetWidth() * size.x, texture->GetHeight() * size.y)
				, 0, 0, texture->GetWidth(), texture->GetHeight(), Gdiplus::UnitPixel, &imageAttr);
			if (-position.x > texture->GetWidth())
				tr->SetPosition({ static_cast<float>(texture->GetWidth()), 0 });
		}
	}

	
	
}


