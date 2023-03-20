
namespace bsp
{
	struct Vertex
	{
		float position[3];
		float normal[3];
		uint8_t color[4];

		float uv[2];
		float st[2];

		float tangent[3];
		float binormal[3];
	};

	namespace lump
	{
		struct Vertices : LumpInterface
		{
			std::vector<Vertex> vertices;
			size_t numvertices;

			virtual bool read_impl(buffer_reader* reader) override
			{
				if (sizeof(bsp::Vertex) != 68)
					perror("wrong size");
				numvertices = this->size() / sizeof(bsp::Vertex);
				for (size_t i = 0; i < numvertices; ++i)
				{
					bsp::Vertex vertex;
					reader->read_type(vertex);
					vertices.push_back(vertex);
				}
				return true;
			}
		};
	} // namespace lump
}	  // namespace bsp