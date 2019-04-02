//
// Created by Ryanm on 01/04/2019.
//

#ifndef ANGRYNERDS_PIGS_H
#define ANGRYNERDS_PIGS_H

#include "Components/GameObject.h"

class Pigs : public GameObject
{
 public:
  Pigs();
  ~Pigs();

 private:
  void LoadSprite();

  int Pigs_Left = 2;
};

#endif // ANGRYNERDS_PIGS_H
