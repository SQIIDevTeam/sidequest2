inline float lerp(float from, float to, float value)
{
	return (1.f - value) * from + value * to;
}