namespace bsp
{
#pragma pack(push, 1)

	struct GfxLightGridColors
	{
		uint8_t rgb[8][3];
//		uint8_t rgb[4][6];
	};
#pragma pack(pop)

	namespace lump
	{
		struct LightGridColors : LumpInterface
		{
			LightGridColors()
			{
			}
			virtual bool read_impl(buffer_reader* reader) override
			{
				size_t numcolors = this->size() / sizeof(GfxLightGridColors);
				int x = 0;
				int y = 0;
				std::vector<unsigned char> image;
				int numpixels = numcolors * 8;
				int width = 64;
				int height = numpixels % width;
				image.resize(numpixels * 3);
				int pixelindex = 0;
				for (size_t i = 0; i < numcolors; ++i)
				{
					GfxLightGridColors c;
					reader->read_type(c);
					for (int k = 0; k < 8; ++k)
					{
						for (int z = 0; z < 3; ++z)
							image[pixelindex + z] = c.rgb[k][z];
						++pixelindex;
					}
				}
				return true;
			}
		};
	} // namespace lump
}	  // namespace bsp