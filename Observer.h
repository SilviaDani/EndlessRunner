//
// Created by user on 17/05/2021.
//

#ifndef ENDLESSRUNNER_OBSERVER_H
#define ENDLESSRUNNER_OBSERVER_H
#include "Player.h"
enum class Event{
    EVENT_DEATH, EVENT_100DISTANCE
};

class Observer {
public:
    virtual ~Observer() {}
    virtual void onNotify(const Player& player, Event event) = 0;
};


#endif //ENDLESSRUNNER_OBSERVER_H
