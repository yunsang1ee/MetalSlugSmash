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
		//find_last_of�� �ش� find�� ���� ��ġ �״ϱ� �ű⿡ +1 �� ���ĺ��� ������������ substr�ϰڴ´ٴ°��� ����?
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
