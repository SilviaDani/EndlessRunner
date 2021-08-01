//
// Created by user on 22/05/2021.
//

#include <iostream>
#include "Achievement.h"

Achievement::Achievement(std::string title, std::string icon) {
    Achievement::title.setString(title);
}

bool Achievement::isUnlocked() const {
    return unlocked;
}

void Achievement::unlock() {
    Achievement::unlocked = true;
}

const sf::Text &Achievement::getTitle() const {
    return title;
}

void AchievementManager::onNotify(const Player &player, Event event) {
    switch (event)
       {
           case Event::EVENT_DEATH:
               if (!player.isAlive())
               {
                   Achievement* ach = new Achievement("First death");
                   if(!isUnlocked(ach)){
                       //TODO a parte il titolo l'achievement è per la morte in genereale, sistema in base ai tipi di morte
                       unlock(ach);
                       achUnlocked.push_back(ach);
                       std::cout<<"You've unlocked MORTEEEEE"<<std::endl;
                   }
               }
               break;
           case Event::EVENT_100DISTANCE:
               Achievement* ach = new Achievement("Runner 100");
               if(!isUnlocked(ach)){
                   unlock(ach);
                   achUnlocked.push_back(ach);
                   std::cout<<"You've unlocked RUNNER 100"<<std::endl;
               }
        }

}

void AchievementManager::unlock(Achievement* achievement) {
    if (!achievement->isUnlocked()) {
        achievement->unlock();
        std::cout<<"BRAVOOOOO!!"<<std::endl; //TODO far apparire un badge
    }
}

bool AchievementManager::isUnlocked(Achievement* ach){
    for(auto i : achUnlocked){
        if (ach->getTitle().getString() == i->getTitle().getString()){
            //Già sbloccato
            delete ach;
            return true;
        }
    }
    return false;
}
