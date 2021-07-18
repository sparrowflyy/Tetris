#pragma once
#include <random>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace GUtils
{
	static int genRandomInt(int min, int max) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(min, max);
		return distrib(gen);
	}

	
}
