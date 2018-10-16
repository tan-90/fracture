#version 400 core

in vec3 localPosition;

out vec3 fragColor;

uniform sampler2D equirectangularMap;

const vec2 invAtan = vec2(0.1591, 0.3183);

vec2 SampleEquirectangularMapAsSphere(vec3 Direction)
{
	vec2 uv = vec2(atan(Direction.z, Direction.x), asin(-Direction.y));
	uv *= invAtan;
	uv += 0.5;
	return uv;
}

void main()
{
	vec2 uv = SampleEquirectangularMapAsSphere(normalize(localPosition));
	fragColor = texture(equirectangularMap, uv).bgr;
}
