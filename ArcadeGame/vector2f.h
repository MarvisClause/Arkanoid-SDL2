#pragma once

class vector2f
{
public:
	float x;
	float y;

	vector2f operator+(vector2f v);
	vector2f operator-(vector2f v);
	vector2f operator*(float f);
	vector2f operator/(float f);
};

