//
// Created by user on 26/02/2021.
//

#ifndef ENDLESSRUNNER_OBSTACLEFACTORY_H
#define ENDLESSRUNNER_OBSTACLEFACTORY_H
#include "Obstacle.h"

class ObstacleFactory {
public:
    virtual Obstacle* factoryMethod()=0;
};

class StoneFactory: public ObstacleFactory{
public:
    Obstacle* factoryMethod() override{
        return new Stone();
    }
};

class RocketFactory: public ObstacleFactory{
public:
    Obstacle* factoryMethod() override{
        return new Rocket();
    }
};

#endif //ENDLESSRUNNER_OBSTACLEFACTORY_H
