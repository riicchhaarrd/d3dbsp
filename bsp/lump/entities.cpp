bool bsp::lump::Entities::read_impl(buffer_reader* reader)
{
	std::string str = reader->read_string();
	parse_entities(str);
	if (entities.empty())
		perror("no worldspawn found");

	parser.parse(&bsp::lump::SunLight::ambient, "ambient");
	parser.parse(&bsp::lump::SunLight::diffusefraction, "diffusefraction");
	parser.parse(&bsp::lump::SunLight::suncolor, "suncolor");
	parser.parse(&bsp::lump::SunLight::sundiffusecolor, "sundiffusecolor");
	parser.parse(&bsp::lump::SunLight::_color, "_color");
	parser.parse(&bsp::lump::SunLight::sundirection, "sundirection");
	parser.parse(&bsp::lump::SunLight::sunlight, "sunlight");

	float intensity = glm::max(sunlight._color.x, glm::max(sunlight._color.y, sunlight._color.z));
	if (sunlight.ambient == 0.f || intensity == 0.f)
	{
		sunlight.computed.ambientcolor = glm::vec3(0.f,0.f,0.f);
	}
	else
	{
		auto c = sunlight._color / intensity;
		sunlight.computed.ambientcolor = sunlight.ambient * c;
	}
	float fac = (sunlight.sunlight - sunlight.ambient) * (1.f - sunlight.diffusefraction);
	sunlight.computed.color = sunlight.suncolor * fac;
	return true;
}
