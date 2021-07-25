#pragma once
#include "GObj.h"

class GObjIntersector {
public:
	GObjIntersector(int iWinWidth, int iWinHeight);
	bool isObjOutWindow(const GObj* iObj1) const;
	static bool intersectObjBoxes(const GObj* iObj1, const GObj* iObj2);
	~GObjIntersector() = default;
protected:
	int m_winWidth;
	int m_winHeight;
};