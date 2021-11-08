//
// Created by nik on 08.11.2021.
//

#include <string>
#include <map>

#ifndef TETRIS_GTIMER_H
class GTimer{
  public:
    GTimer() = default;
    void addTimeTickS(float iTime);
    void addEvent(const std::string& iEventName, float iPeriod);
    void setNewPeriod(const std::string& iEventName, float iPeriod);
    bool isEventReady(const std::string& iEventName);

    ~GTimer() = default;
private:
    struct EventTimer {
        EventTimer() = default;
        explicit EventTimer (float iPeriod) :period(iPeriod), elapsedTime(0.0),ready(false) {};
        bool operator()( const EventTimer& iEventTimer1, const EventTimer& iEventTimer2) const{
          return iEventTimer1.period < iEventTimer2.period;
        };
        void addTime(float iTime) {
          elapsedTime += iTime;
          ready = elapsedTime > period;
        }
        void restart() {elapsedTime = 0.0; ready = false;}
        float period;
        float elapsedTime;
        bool ready;

    };
    std::map<std::string, EventTimer> eventsReadiness;
};
#define TETRIS_GTIMER_H

#endif //TETRIS_GTIMER_H
