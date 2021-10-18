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
    float posX = player.getPosition().x;
    float posY = player.getPosition().y;
    AchievementManager* am = new AchievementManager();
    map.addObserver(am); //need this and the previous line in order to use correctly "checkCollisions" method

    //COIN
    map.instantiateCoin();
    ASSERT_EQ(map.getCoins().size(), 1);
    while (player.getPosition().y >= map.getCoins().at(0).getPosition().y){
        player.move(true);
    }
    while (map.getCoins().at(0).getPosition().x >= player.getPosition().x){
        map.moveCoin();
    }
    EXPECT_TRUE(player.getGlobalBounds().intersects(map.getCoins().at(0).getGlobalBounds()));
    map.checkCollisions(player);
    EXPECT_EQ(map.getPickedCoins(), 1);
    ASSERT_EQ(map.getCoins().size(), 0);

    map.instantiateCoin();
    player.setPosition(0,0);
    ASSERT_EQ(map.getCoins().size(), 1);
    map.setPositionCoin(0, 0, 0);
    EXPECT_TRUE(player.getGlobalBounds().intersects(map.getCoins().at(0).getGlobalBounds()));
    map.checkCollisions(player);
    EXPECT_EQ(map.getPickedCoins(), 2);
    ASSERT_EQ(map.getCoins().size(), 0);

    //POWER UP
    sf::Clock clock;

    player.setPosition(posX, posY);
    while (clock.getElapsedTime().asSeconds()<=5){}
    map.instantiatePowerUp(player);
    ASSERT_EQ(map.getPowerUp().size(), 1);
    while (player.getPosition().y >= map.getPowerUp().at(0).getPosition().y){
        player.move(true);
    }
    while (map.getPowerUp().at(0).getPosition().x >= player.getPosition().x){
        map.movePowerUp();
    }
    EXPECT_TRUE(player.getGlobalBounds().intersects(map.getPowerUp().at(0).getGlobalBounds()));
    map.checkCollisions(player);
    EXPECT_TRUE(dynamic_cast<Giant*>(player.getForm()) || dynamic_cast<Bike*>(player.getForm()) || dynamic_cast<GravityInverter*>(player.getForm()));
    ASSERT_EQ(map.getPowerUp().size(), 0);
    player.changeForm();
    clock.restart();

    player.setPosition(0,0);
    while (clock.getElapsedTime().asSeconds()<=5){}
    map.instantiatePowerUp(player);
    ASSERT_EQ(map.getPowerUp().size(), 1);
    map.setPowerUpPosition(0, 0);
    EXPECT_TRUE(player.getGlobalBounds().intersects(map.getPowerUp().at(0).getGlobalBounds()));
    map.checkCollisions(player);
    EXPECT_TRUE(dynamic_cast<Giant*>(player.getForm()) || dynamic_cast<Bike*>(player.getForm()) || dynamic_cast<GravityInverter*>(player.getForm()));
    ASSERT_EQ(map.getPowerUp().size(), 0);
    player.changeForm();

    //OBSTALCE
    map.instantiateObstacle();
    ASSERT_EQ(map.getObstacles().size(), 1);
    player.setPosition(posX,posY);
    map.getObstacles().at(0)->setPosition(posX, map.getObstacles().at(0)->getObstacleSprite().getPosition().y);
    while (player.getPosition().y >= map.getObstacles().at(0)->getObstacleSprite().getPosition().y){
        player.move(true);
    }
    while (map.getObstacles().at(0)->getObstacleSprite().getPosition().x >= player.getPosition().x){
        map.moveObstacle();
    }
    EXPECT_TRUE(player.getGlobalBounds().intersects(map.getObstacles().at(0)->getObstacleSprite().getGlobalBounds()));
    map.checkCollisions(player);
    ASSERT_FALSE(player.isAlive());
    ASSERT_EQ(map.getObstacles().size(), 0);

    player.reset();
    ASSERT_TRUE(player.isAlive());
    map.instantiateObstacle();
    ASSERT_EQ(map.getObstacles().size(), 1);
    player.setPosition(0,0);
    map.getObstacles().at(0)->setPosition(0,0);
    ASSERT_TRUE(player.getGlobalBounds().intersects(map.getObstacles().at(0)->getObstacleSprite().getGlobalBounds()));
    map.checkCollisions(player);
    ASSERT_FALSE(player.isAlive());
    ASSERT_EQ(map.getObstacles().size(), 0);
}


