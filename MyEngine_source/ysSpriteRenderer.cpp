#include "ysSpriteRenderer.h"
#include "ysGameObject.h"
#include "ysTransform.h"
#include "ysTexture.h"
#include "ysRenderer.h"
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

	auto position = renderer::mainCamera->CalculatPosition(tr->GetPosition());

	if (texture->GetTextureType() == graphics::Texture::TextureType::Bmp)
	{
		auto check = TransparentBlt(hDC, position.x, position.y, texture->GetWidth() * size.x, texture->GetHeight() * size.y
			, texture->GetDC(), 0, 0, texture->GetWidth(), texture->GetHeight(), RGB(255, 0, 255));
		//시작위치 끝위치 정할수있어야	함
		//
		assert(check);
	}
	else if (texture->GetTextureType() == graphics::Texture::TextureType::Png)
	{
		Gdiplus::Graphics graphics(hDC);
		Gdiplus::ImageAttributes imageAttr;	
		imageAttr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255));

		graphics.DrawImage(texture->GetImage()
			, Gdiplus::Rect(position.x, position.y, texture->GetWidth() * size.x, texture->GetHeight() * size.y)
			, 0, 0, texture->GetWidth(), texture->GetHeight(), Gdiplus::UnitPixel, &imageAttr);
		if (-position.x > texture->GetWidth())
			tr->SetPosition({ static_cast<float>(texture->GetWidth()), 0 });
	}
}


