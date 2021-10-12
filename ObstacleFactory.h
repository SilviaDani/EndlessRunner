//
// Created by user on 26/02/2021.
//

#ifndef ENDLESSRUNNER_OBSTACLEFACTORY_H
#define ENDLESSRUNNER_OBSTACLEFACTORY_H
#include "Obstacle.h"

enum class ObstacleList{
    Rocket, Stone
};

class ObstacleFactory {
public:
    Obstacle* factoryMethod(ObstacleList obstacle);
};

#endif //ENDLESSRUNNER_OBSTACLEFACTORY_H
