
namespace bsp
{
#pragma pack(push, 1)

	struct RGBA8
	{
		uint8_t r, g, b, a;
	};
	struct LightmapImage
	{
		RGBA8 r[512 * 512];
		RGBA8 g[512 * 512];
		RGBA8 b[512 * 512];
		uint8_t shadowmap[1024 * 1024];

		std::vector<RGBA8> generate_fix(const glm::vec3 &color)
		{
			std::vector<RGBA8> image;
			image.resize(512 * 512);
			for (int x = 0; x < 512; ++x)
			{
				for (int y = 0; y < 512; ++y)
				{
					int i = y * 512 + x;
					float alpha_value = shadowmap[(y * 2) * 1024 + (x * 2)];
#if 0
					// take more samples
					unsigned char* sm = &shadowmap[(y * 2) * 1024 + (x * 2)];
					float sample1 = sm[0];
					float sample2 = sm[1];
					float sample3 = sm[2];
					float sample4 = sm[3];
					float alpha_value = (sample1 + sample2 + sample3 + sample4) / 4.f;
#endif
					int red_value = (r[i].r + alpha_value * color.r) * 0.5f;
					int green_value = (g[i].r + alpha_value * color.g) * 0.5f;
					int blue_value = (b[i].r + alpha_value * color.b) * 0.5f;

					if (red_value - 255 >= 0)
						red_value = 255;
					if (green_value - 255 >= 0)
						green_value = 255;
					if (blue_value - 255 >= 0)
						blue_value = 255;
					image[i].b = blue_value;
					image[i].g = green_value;
					image[i].r = red_value;
					image[i].a = 255;
				}
			}
			return image;
		}

		void compute(std::vector<RGBA8>& computed)
		{
			computed.resize(512 * 512);
			for (size_t i = 0; i < 512 * 512; ++i)
			{
				RGBA8 rgba;
				rgba.r = r->r;
				rgba.g = g->g;
				rgba.b = b->b;
				rgba.a = 255;
				computed[i] = rgba;
			}
		}
	};
#pragma pack(pop)

	namespace lump
	{
		struct Lightmaps : LumpInterface
		{
			std::vector<std::unique_ptr<LightmapImage>> lightmaps;
			Lightmaps()
			{
			}
			virtual ~Lightmaps()
			{
			}
			virtual bool read_impl(buffer_reader* reader) override
			{
				size_t numlightmaps = this->size() / (1 << 22);
				if (sizeof(LightmapImage) != (1 << 22))
					perror("lightmap wrong size");
				for (size_t i = 0; i < numlightmaps; ++i)
				{
					auto lmap = std::make_unique<LightmapImage>();
					reader->read_type(*lmap.get());

					lightmaps.push_back(std::move(lmap));
				}
				return true;
			}
		};
	} // namespace lump
}	  // namespace bsp