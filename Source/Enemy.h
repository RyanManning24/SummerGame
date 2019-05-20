//
// Created by Ryanm on 17/05/2019.
//

#ifndef ANGRYNERDS_ENEMY_H
#define ANGRYNERDS_ENEMY_H

#include "Components/GameObject.h"

class Enemy
{
 public:
  Enemy();
  ~Enemy();

  void gameobjectSetup();

 private:
  GameObject Sprite;
  GameObject Enemy_Tears;

  float Enemy_Xpos;
  float Enemy_Ypos;

  int EnemyHealth = 3;
};

#endif // ANGRYNERDS_ENEMY_H
