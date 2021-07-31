//
// Created by user on 23/05/2021.
//

#ifndef ENDLESSRUNNER_SUBJECT_H
#define ENDLESSRUNNER_SUBJECT_H
#include "Observer.h"

class Subject {
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
protected:
    std::vector<Observer*> observers;
    void notify(const Player& player, Event event);
};


#endif //ENDLESSRUNNER_SUBJECT_H
