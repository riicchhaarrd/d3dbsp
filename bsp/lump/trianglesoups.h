
namespace bsp
{
#pragma pack(push, 1)
#define LIGHTMAP_NONE (31)

	struct TriangleSoup
	{
		uint16_t material_id;

		uint16_t lightmap_id;

		uint32_t vertex_offset;
		uint16_t vertex_length;

		uint16_t triangle_length;
		uint32_t triangle_offset;
	};
#pragma pack(pop)

	namespace lump
	{
		//really just meshes/bodygroups e.g see source engine
		struct TriangleSoups : LumpInterface
		{
			std::vector<bsp::TriangleSoup> trianglesoups;
			size_t numtrianglesoups;
			virtual bool read_impl(buffer_reader* reader) override
			{
				numtrianglesoups = this->size() / sizeof(bsp::TriangleSoup);
				trianglesoups.resize(numtrianglesoups);
				reader->read(trianglesoups.data(), sizeof(bsp::TriangleSoup), numtrianglesoups);
				#if 0
				for (auto& ts : trianglesoups)
				{
					printf("lightmap_id=%d\n", ts.lightmap_id);
				}
				#endif
				return true;
			}
		};
	} // namespace lump
}	  // namespace bsp