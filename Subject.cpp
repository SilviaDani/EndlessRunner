//
// Created by user on 23/05/2021.
//

#include "Subject.h"

void Subject::addObserver(Observer *observer) {
    observers.push_back(observer);
}

void Subject::removeObserver(Observer *observer) {
    if (observers.size() != 0){
        auto position = std::find(observers.begin(),observers.end(), observer);
        if (position != observers.end())
            observers.erase(position);
    }
}

void Subject::notify(const Player &player, Event event) {
    observers.at(0)->onNotify(player, event);
  //  for (auto i : observers)
       // i->onNotify(player, event);
}
