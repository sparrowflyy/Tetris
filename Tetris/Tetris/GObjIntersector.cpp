#include "GObjIntersector.h"

GObjIntersector::GObjIntersector(int iWinWidth, int iWinHeight)
	:m_winRect(0,0, float(iWinWidth),float(iWinHeight))
{
}

bool GObjIntersector::intersectObjBoxes(const GObj* iObj1, const GObj* iObj2, sf::FloatRect& oIntersection)
{
	return iObj1->getExtents().intersects(iObj2->getExtents(), oIntersection);
}

bool GObjIntersector::intersectObjBoxWindow(const GObj* iObj1, sf::FloatRect& oIntersection) const {
	sf::FloatRect ext = iObj1->getExtents();
	ext.intersects(m_winRect, oIntersection);
	return ext != oIntersection;
}
