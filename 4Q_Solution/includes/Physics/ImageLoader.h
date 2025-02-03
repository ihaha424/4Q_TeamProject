#pragma once

namespace PhysicsEngineAPI
{
	class ImageLoader
	{
	public:
		struct Image
		{
			int width;
			int height;
			int channels;
			unsigned char* data;

			~Image();
		};
	public:
		bool operator()(
			Image& data,
			const char* filePath,
			int channel = 0
			);

	};
}
