// reference: https://wiki.zeroy.com/index.php?title=Call_of_Duty_2:_d3dbsp

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>

#include "buffer_reader.h"
#include "bsp/world.h"

#pragma pack(push, 1)
struct Header
{
	uint8_t magic[4];
	uint8_t version[4];
};
#pragma pack(pop)
int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Usage: %s <bsp_file>\n", argv[0]);
		return 0;
	}
	std::ifstream in(argv[1], std::ios::ate | std::ios::binary);
	if (!in.is_open())
	{
		printf("Failed to open '%s'\n", argv[1]);
		return 0;
	}
	size_t file_size = in.tellg();
	in.seekg(std::ios::beg);
	std::vector<char> v;
	v.resize(file_size);
	in.read(v.data(),file_size);
	
	auto reader = std::make_unique<BufferReader>(v.data(), v.size());

	bsp::Header hdr;
	//fread(&hdr, sizeof(bsp::Header), 1, stream);
	if(!reader->read(&hdr, 1, sizeof(hdr))
		return 1;
	assert(!memcmp(hdr.magic, "IBSP", 4));
	assert(hdr.version[0] == 0x4);
	assert(hdr.version[1] == 0x0);
	assert(hdr.version[2] == 0x0);
	assert(hdr.version[3] == 0x0);

	size_t nlumps = 0;
	std::map<bsp::LumpName, bsp::LumpEntry> entries;
	while (1)
	{
		bsp::LumpEntry entry;
		reader->read(&entry.size, 1, sizeof(entry.size));
		reader->read(&entry.offset, 1, sizeof(entry.offset));
		//fread(&entry.size, sizeof(entry.size), 1, stream);
		//fread(&entry.offset, sizeof(entry.offset), 1, stream);
		if (entry.offset == 0 && entry.size == 0)
			break;
		//printf("offs=%d,sz=%d\n", entry.offset, entry.size);
		entries[(bsp::LumpName)nlumps++] = entry;
	}
	printf("%d lumps\n", nlumps);

	std::map<bsp::LumpName, bsp::LumpInterface*> lumps = {
		{bsp::LumpName::kMaterial, &resource.materials},
		{bsp::LumpName::kLightmaps, &resource.lightmaps},
		{bsp::LumpName::kLightGridPoints, &resource.lightgridpoints},
		{bsp::LumpName::kLightGridColors, &resource.lightgridcolors},
		{bsp::LumpName::kTriangles, &resource.triangles},
		{bsp::LumpName::kTriangleSoups, &resource.triangle_soups},
		{bsp::LumpName::kVertices, &resource.vertices},
		{bsp::LumpName::kEntities, &resource.entities}
	};
	for(auto & iter : lumps)
	{
		//fseek(stream, entries[iter.first].offset, SEEK_SET);
		iter.second->read(reader.get(), entries[iter.first]);
	}
	//after loaded process the lightmaps
	for (int g = 0; g < world.lightmaps.lightmaps.size(); ++g)
	{
		auto* lm = world.lightmaps.lightmaps[g].get();

		Image shadowmap(1024, 1024, 255, 255, 255, 255);
		for (size_t x = 0; x < 1024; ++x)
		{
			for (int y = 0; y < 1024; ++y)
			{
				auto& sm = lm->shadowmap;
				uint8_t val = sm[y * 1024 + x];
				shadowmap[x][y] = RGBA(val, val, val, 255);
			}
		}
		auto fixed = lm->generate_fix(world.entities.sunlight.computed.color);
		Image sampler(512, 512, 4, (u8*)fixed.data());
		//TODO: write the fixed/baked image to image...
	}
}