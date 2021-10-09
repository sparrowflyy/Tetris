#pragma once
#include "GObj.h"

//struct IntersectionInfo
//{
//	bool left = false;
//	bool right = false;
//	bool top = false;
//	bool bottom = false;
//	IntersectionInfo() = default;
//};

class GObjIntersector {
public:
	GObjIntersector(int iWinWidth, int iWinHeight);
	bool intersectObjBoxWindow(const GObj* iObj1, sf::FloatRect& oIntersection) const;
	static bool intersectObjBoxes(const GObj* iObj1, const GObj* iObj2, sf::FloatRect& oIntersection);
	static bool compareBoxes(const sf::FloatRect& box1, const sf::FloatRect& box2, double tol = 1e-3);
	~GObjIntersector() = default;
protected:
	sf::FloatRect m_winRect;
};
