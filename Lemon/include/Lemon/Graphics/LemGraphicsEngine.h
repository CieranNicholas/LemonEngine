#pragma once
#include <Lemon/Math/LemVec4.h>
class LemGraphicsEngine
{
public:
	LemGraphicsEngine();
	~LemGraphicsEngine();

	void clear(const LemVec4& color);
};

