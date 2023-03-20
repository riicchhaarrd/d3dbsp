namespace bsp
{
#pragma pack(push, 1)
	struct Triangle
	{
		uint16_t vertex[3];
	};
#pragma pack(pop)

	namespace lump
	{
		// really just the faces/indices
		struct Triangles : LumpInterface
		{
			std::vector<bsp::Triangle> triangles;
			size_t numtriangles;
			virtual bool read_impl(buffer_reader* reader) override
			{
				numtriangles = this->size() / sizeof(bsp::Triangle);
				triangles.resize(numtriangles);
				reader->read(triangles.data(), sizeof(bsp::Triangle), numtriangles);
				// fread(triangles.data(), sizeof(bsp::Triangle), numtriangles, stream);
				return true;
			}
		};
	} // namespace lump
}	  // namespace bsp