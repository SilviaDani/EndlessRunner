//
// Created by user on 26/02/2021.
//

#include "ObstacleFactory.h"

Obstacle *ObstacleFactory::factoryMethod(ObstacleList obstacle) {
    if (obstacle == ObstacleList::Stone){
        return new Stone();
    }
    else if (obstacle == ObstacleList::Rocket){
        return new Rocket();
    }
    else
        return nullptr;
}
