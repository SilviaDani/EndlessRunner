//
// Created by user on 17/05/2021.
//

#ifndef ENDLESSRUNNER_OBSERVER_H
#define ENDLESSRUNNER_OBSERVER_H
#include "Player.h"
enum class EventType{
    EVENT_DEATH, EVENT_100DISTANCE
};

class Observer {
public:
    virtual ~Observer() {}
    virtual void onNotify(const Player& player, EventType event) = 0;
};


#endif //ENDLESSRUNNER_OBSERVER_H
