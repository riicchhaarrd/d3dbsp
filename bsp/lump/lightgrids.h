
namespace bsp
{
#pragma pack(push, 1)

	struct GfxLightGridPoint
	{
		uint8_t xyzHighBits[4];
		uint8_t xyzLowBitsAndSunVisible;
		uint8_t needsTrace;
		uint16_t colorsIndex;
	};
#pragma pack(pop)

	namespace lump
	{
		struct LightGridPoints : LumpInterface
		{
			LightGridPoints()
			{
			}
			virtual bool read_impl(buffer_reader* reader) override
			{
				size_t numlightgrids = this->size() / sizeof(GfxLightGridPoint);
				//printf("%d points\n", numlightgrids);
				for (size_t i = 0; i < numlightgrids; ++i)
				{
					GfxLightGridPoint pt;
					reader->read_type(pt);
					//printf("pt coloridx=%d,needstrace=%d,xyz=%d,%d,%d,%d sunvisible=%d\n", pt.colorsIndex, pt.needsTrace, pt.xyzHighBits[0], pt.xyzHighBits[1], pt.xyzHighBits[2], pt.xyzHighBits[3], pt.xyzLowBitsAndSunVisible);
				}
				return true;
			}
		};
	} // namespace lump
}	  // namespace bsp