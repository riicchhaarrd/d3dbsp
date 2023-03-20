namespace bsp
{
	struct Material
	{
		char name[64];
		uint8_t flags[2][4];
	};
	namespace lump
	{
		struct Materials : LumpInterface
		{
			size_t nummaterials;
			std::vector<bsp::Material> materials;
			std::unordered_map<std::string, int> material_to_id;

			Materials()
			{
			}
			virtual ~Materials()
			{
			}
			virtual bool read_impl(buffer_reader* reader) override
			{
				nummaterials = this->size() / sizeof(bsp::Material);
				for (size_t i = 0; i < nummaterials; ++i)
				{
					bsp::Material material;
					reader->read_type(material);
					// printf("material: %s\n", material.name);
					material_to_id[material.name] = materials.size();
					materials.push_back(material);
				}
				return true;
			}
		};
	} // namespace lump
}	  // namespace bsp