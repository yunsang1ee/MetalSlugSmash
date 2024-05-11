#include "ysTexture.h"

namespace ys::graphics
{
	Texture::Texture() 
		: Resource(enums::ResourceType::Texture)
	{
	}

	Texture::~Texture()
	{
	}
	HRESULT Texture::Load(const std::wstring& path)
	{
		//bmp
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);
		//find_last_of는 해당 find의 값의 위치 그니까 거기에 +1 그 이후부터 마지막까지를 substr하겠는다는거임 ㅇㅋ?
		if (ext == L"bmp")
		{
			
		}
		else if (ext == L"png")
		{
			image = Gdiplus::Image::FromFile(path.c_str());
			width = image->GetWidth();
			height = image->GetHeight();
		}
		//png
	/*	*/
		return E_NOTIMPL;
	}
}
