#include "pch.h"
#include "ImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace PhysicsEngineAPI
{
	bool ImageLoader::operator()(Image& data, const char* filePath, int channel)
	{
		data.data = stbi_load(filePath, &data.width, &data.height, &data.channels, channel);
		if (nullptr == data.data)
			return false;
		return true;
	}
	ImageLoader::Image::~Image()
	{
		stbi_image_free(data);
	}
}

