#include "vector2f.h"

vector2f vector2f::operator+(vector2f v)
{
	vector2f result;
	result.x = x + v.x;
	result.y = y + v.y;
	return result;
}

vector2f vector2f::operator-(vector2f v)
{
	vector2f result;
	result.x = x - v.x;
	result.y = y - v.y;
	return result;
}

vector2f vector2f::operator/(float f)
{
	vector2f result;
	result.x = x / f;
	result.y = y / f;
	return result;
}


vector2f vector2f::operator*(float f)
{
	vector2f result;
	result.x = x * f;
	result.y = y * f;
	return result;
}
//What is the meaning of living?