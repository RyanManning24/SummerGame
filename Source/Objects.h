//
// Created by Ryanm on 01/04/2019.
//

#ifndef ANGRYNERDS_OBJECTS_H
#define ANGRYNERDS_OBJECTS_H

#include "Components/GameObject.h"

class Objects : public GameObject
{
 public:
  Objects();
  ~Objects();

 private:
  int Times_hit = 0;
  int Number_Of_Objects = 0;
};

#endif // ANGRYNERDS_OBJECTS_H
