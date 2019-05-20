//
// Created by Ryanm on 17/05/2019.
//

#ifndef ANGRYNERDS_PLAYER_H
#define ANGRYNERDS_PLAYER_H

#include "Components/GameObject.h"

class Player
{
 public:
  Player();
  ~Player();

  void gameobjectSetup();

 private:
  GameObject Sprite;
  GameObject Player_Tears;

  float X_pos = 910;
  float Y_pos = 540;

  float lives = 3;
};

#endif // ANGRYNERDS_PLAYER_H
