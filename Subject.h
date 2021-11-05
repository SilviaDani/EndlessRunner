//
// Created by user on 23/05/2021.
//

#ifndef ENDLESSRUNNER_SUBJECT_H
#define ENDLESSRUNNER_SUBJECT_H
#include "Observer.h"

class Subject {
public:
    virtual void addObserver(Observer* observer);
    virtual void removeObserver(Observer* observer);
protected:
    std::vector<Observer*> observers;
    virtual void notify(const Player& player, EventType event);
};


#endif //ENDLESSRUNNER_SUBJECT_H
