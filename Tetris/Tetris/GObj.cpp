#include "GObj.h"

#include <iostream>

void GObj::addUniqueEvent(const GEvent* iEvent) {

	if (std::find_if(m_events.begin(), m_events.end(), [&iEvent](const GEvent* a)
	{
		if (a->type == iEvent->type) {
			if (a->type==GEvent::EventType::Motion) {
				return ((GEventMotion*)(a))->getMotion() == ((GEventMotion*)(iEvent))->getMotion();
			}
			return true;
		}
		return false;
	}) == m_events.end())
	{

		m_events.push_back(iEvent);
		std::cout << "Event added: " << m_events.size()<<std::endl;
	}

}
