#include "ysSpriteRenderer.h"
#include "ysGameObject.h"
#include "ysTransform.h"

ys::SpriteRenderer::SpriteRenderer()
	: Component(enums::ComponentType::SpriteRenderer)
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
	auto tr = GetOwner()->GetComponent<Transform>();
	auto position = tr->GetPosition();

	Gdiplus::Graphics graphics(hDC);
	Gdiplus::ImageAttributes imageAttr;
	imageAttr.SetColorKey(Gdiplus::Color(255, 0, 255), Gdiplus::Color(255, 0, 255));
	const auto& name = getName();
	/*if(name == L"SRBackBack")
	{
		graphics.DrawImage(image, Gdiplus::Rect(0, 0, 4 * 300, 3 * 300), position.x, position.y + 400, 4 * 300, 3 * 250, Gdiplus::UnitPixel, &imageAttr);
	}
	else if(name == L"SRBack")
	{
		graphics.DrawImage(image, Gdiplus::Rect(0, 0, 4 * 300, 3 * 300), position.x, position.y + 300, 4 * 300, 3 * 250, Gdiplus::UnitPixel, &imageAttr);
	}
	else if (name == L"SR")
	{
		graphics.DrawImage(image, Gdiplus::Rect(position.x, position.y, width, height), 0, 0, width, height, Gdiplus::UnitPixel, &imageAttr);
	}
	else if (name == L"SRTilte1")
	{
		graphics.DrawImage(image, Gdiplus::Rect(position.x, position.y, width, height), 0, 0, width, height / 2, Gdiplus::UnitPixel, &imageAttr);
		if (-position.x > width)
			tr->SetPosition({ static_cast<float>(width), 0 });
	}
	else if (name == L"SRTilte2")
	{
		graphics.DrawImage(image, Gdiplus::Rect(position.x, position.y, width, height), 0, 0, width, height / 2, Gdiplus::UnitPixel, &imageAttr);
		if (-position.x > width)
			tr->SetPosition({ static_cast<float>(width), 0 });
	}*/
}


