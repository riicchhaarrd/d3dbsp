
namespace bsp
{
	namespace lump
	{
		struct SunLight
		{
			Vec3 sundiffusecolor;
			Vec3 _color;
			float diffusefraction;
			float ambient;
			Vec3 sundirection;
			Vec3 suncolor;
			float sunlight;

			struct Computed
			{
				Vec3 color;
				Vec3 ambientcolor;
			} computed;
		};

		struct Entity
		{
			std::unordered_map<std::string, std::string> kvp;
		};

		struct Entities : LumpInterface
		{
			SunLight sunlight;
			std::vector<Entity> entities;
			virtual bool read_impl(buffer_reader* reader) override;
		};
	} // namespace lump;
} // namespace bsp;