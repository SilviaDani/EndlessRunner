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


void AchievementManager::onNotify(const Player &player, Event event) {
    switch (event)
       {
           case Event::EVENT_DEATH:
               if (!player.isAlive())
               {
                   Achievement* ach = new Achievement("First death");
                   //TODO a parte il titolo l'achievement è per la morte in genereale, sistema in base ai tipi di morte
                   unlock(ach);
                   std::cout<<"You've unlocked MORTEEEEE"<<std::endl;
               }
               break;
                // Handle other events...
        }

}

void AchievementManager::unlock(Achievement* achievement) {
    if (!achievement->isUnlocked()) {
        achievement->unlock();
        std::cout<<"BRAVOOOOO!!"<<std::endl; //TODO far apparire un badge
    }
}
