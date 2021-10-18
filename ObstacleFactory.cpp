//
// Created by user on 26/02/2021.
//

#include "ObstacleFactory.h"

Obstacle *ObstacleFactory::factoryMethod(ObstacleType obstacle) {
    if (obstacle == ObstacleType::Stone){
        return new Stone();
    }
    else if (obstacle == ObstacleType::Rocket){
        return new Rocket();
    }
    else
        return nullptr;
}
