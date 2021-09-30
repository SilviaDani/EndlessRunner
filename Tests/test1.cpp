//
// Created by user on 30/09/2021.
//

#include "gtest/gtest.h"
#include "../Map.h"

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
    player.kill();
    ASSERT_FALSE(player.isAlive());
}

TEST(map_testing, instantiatingCoins){
   Map map;
   map.instantiateCoin();
   ASSERT_EQ(map.getCoinsSize(), 1);
}