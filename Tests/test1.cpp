//
// Created by user on 30/09/2021.
//

#include "gtest/gtest.h"
#include "../Map.h"
#include "../Game.h"

TEST(player_testing, player_state){
    Player player;
    int nGravityInverter = 0, nGiant = 0, nBike = 0;
    for (int i = 0; i<21; i++){
        player.changeForm();
        Giant* formG = dynamic_cast<Giant*>(player.getForm());
        Bike* formB = dynamic_cast<Bike*>(player.getForm());
        if (formG)
            nGiant++;
        else if (formB)
            nBike++;
        else
            nGravityInverter++;
        player.changeForm();
    }
    ASSERT_TRUE((nGravityInverter + 3 <= nBike || nGravityInverter - 3 <= nBike) && (nBike + 3 <= nGiant || nBike - 3 <= nGiant)
        && (nGiant + 3 <= nGravityInverter || nGiant - 3 <= nGravityInverter));
}

TEST(map_testing, collisions){
    Map map;
    Player player;
    AchievementManager* am = new AchievementManager();
    map.addObserver(am); //need this and the previous line in order to use correctly "checkCollisions" method

    //COIN
    map.instantiateCoin();
    player.setPosition(0,0);
    ASSERT_EQ(map.getCoins().size(), 1);
    map.setPositionCoin(0, 0, 0);
    EXPECT_TRUE(player.getGlobalBounds().intersects(map.getCoins().at(0).getGlobalBounds()));
    map.checkCollisions(player);
    EXPECT_EQ(map.getPickedCoins(), 1);

    player.setPosition(0,0);
    //POWER UP
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds()<=5){}
    map.instantiatePowerUp(player);
    ASSERT_EQ(map.getPowerUp().size(), 1);
    map.setPowerUpPosition(0, 0);
    EXPECT_TRUE(player.getGlobalBounds().intersects(map.getPowerUp().at(0).getGlobalBounds()));
    map.checkCollisions(player);
    EXPECT_TRUE(dynamic_cast<Giant*>(player.getForm()) || dynamic_cast<Bike*>(player.getForm()) || dynamic_cast<GravityInverter*>(player.getForm()));
    player.changeForm();

    //OBSTALCE
    map.instantiateObstacle();
    ASSERT_EQ(map.getObstacles().size(), 1);
    player.setPosition(0,0);
    map.getObstacles().at(0)->setPosition(0,0);
    ASSERT_TRUE(player.getGlobalBounds().intersects(map.getObstacles().at(0)->getObstacleSprite().getGlobalBounds()));
    map.checkCollisions(player);
    ASSERT_FALSE(player.isAlive());
}


