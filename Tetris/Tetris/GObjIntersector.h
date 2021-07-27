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
	~GObjIntersector() = default;
protected:
	sf::FloatRect m_winRect;
};
