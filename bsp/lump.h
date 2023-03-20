
namespace bsp
{
	enum class LumpName : int32_t
	{
		kMaterial,
		kLightmaps,
		kLightGridPoints,
		kLightGridColors,

		kPlanes = 4,
		kTriangleSoups = 7,
		kVertices,
		kTriangles,
		kEntities = 37
	};

#pragma pack(push, 1)
	struct LumpEntry
	{
		int32_t offset, size;
	};
#pragma pack(pop)

	struct LumpInterface
	{
		LumpEntry entry;
		size_t size()
		{
			return entry.size;
		}
		size_t offset()
		{
			return entry.offset;
		}
		LumpInterface()
		{
		}
		virtual ~LumpInterface()
		{
		}
		virtual bool read_impl(buffer_reader*) = 0;
		bool read(buffer_reader* reader, LumpEntry& _entry)
		{
			this->entry = _entry;
			reader->set_cursor(entry.offset);
			// fseek(stream, entry.offset, SEEK_SET);
			return read_impl(reader);
		}
	};
}; // namespace bsp