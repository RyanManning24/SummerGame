//
// Created by Ryanm on 01/04/2019.
//
#include "Components/GameObject.h"

#ifndef ANGRYNERDS_BIRDS_H
#  define ANGRYNERDS_BIRDS_H

class Birds : public GameObject
{
 public:
  Birds();
  ~Birds();

 private:
  float BirdsMovement();
};

#endif // ANGRYNERDS_BIRDS_H
