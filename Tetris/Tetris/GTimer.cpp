//
// Created by nik on 08.11.2021.
//
#include "GTimer.h"

void GTimer::addEvent(const std::string &iEventName, float iPeriod) {
  eventsReadiness[iEventName] = EventTimer(iPeriod);
}

void GTimer::setNewPeriod(const std::string &iEventName, float iPeriod) {
  eventsReadiness[iEventName].period = iPeriod;
}
void GTimer::addTimeTickS(float iTime) {
  for (auto& [name,timer] : eventsReadiness){
    timer.addTime(iTime);
  }
}

bool GTimer::isEventReady(const std::string &iEventName) {
  bool ready = eventsReadiness[iEventName].ready;
  if (ready) {
    eventsReadiness[iEventName].restart();
  }
  return ready;
}
