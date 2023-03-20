#pragma once

#include <map>
#include <unordered_map>

#include "lump.h"
#include "lump/entities.h"
#include "lump/lightmaps.h"
#include "lump/lightgrids.h"
#include "lump/lightgridcolors.h"
#include "lump/triangles.h"
#include "lump/trianglesoups.h"
#include "lump/materials.h"
#include "lump/vertices.h"

namespace bsp
{
	struct World
	{
		lump::Materials materials;
		lump::Lightmaps lightmaps;
		lump::LightGridPoints lightgridpoints;
		lump::LightGridColors lightgridcolors;
		lump::Triangles triangles;
		lump::Vertices vertices;
		lump::TriangleSoups triangle_soups;
		lump::Entities entities;
	};
}; // namespace bsp