#include "GObjIntersector.h"

GObjIntersector::GObjIntersector(int iWinWidth, int iWinHeight)
	: m_winWidth(iWinWidth)
	, m_winHeight(iWinHeight)
{
}

bool GObjIntersector::intersectObjBoxes(const GObj* iObj1, const GObj* iObj2)
{
	return iObj1->getExtents().intersects(iObj2->getExtents());
}

bool GObjIntersector::isObjOutWindow(const GObj* iObj1) const {
	sf::FloatRect ext = iObj1->getExtents();
	
	return ext.left < 0 || ext.width + ext.left > m_winWidth || ext.top + ext.height > m_winHeight;
}
