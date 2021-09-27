#include "GObjIntersector.h"

bool GObjIntersector::compareBoxes(const sf::FloatRect& box1, const sf::FloatRect& box2, double tol) {
	return abs(box1.left - box2.left) < tol && abs(box1.top - box2.top) < tol
		&& abs(box1.width - box2.width) < tol && abs(box1.height - box2.height) < tol;
	
}
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
	return !compareBoxes(ext, oIntersection);
}
