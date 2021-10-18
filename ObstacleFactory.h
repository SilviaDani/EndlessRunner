//
// Created by user on 26/02/2021.
//

#ifndef ENDLESSRUNNER_OBSTACLEFACTORY_H
#define ENDLESSRUNNER_OBSTACLEFACTORY_H
#include "Obstacle.h"

enum class ObstacleType{
    Rocket, Stone
};

class ObstacleFactory {
public:
    Obstacle* factoryMethod(ObstacleType obstacle);
};

#endif //ENDLESSRUNNER_OBSTACLEFACTORY_H
