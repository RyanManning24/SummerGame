//
// Created by Ryanm on 01/04/2019.
//
#include "Components/GameObject.h"

#ifndef ANGRYNERDS_BIRDS_H
#  define ANGRYNERDS_BIRDS_H

//@Feedback: this class is not needed
class Bird : public GameObject
{
 public:
  Bird();

  //@feedback: you must override the base destructor to prevent memory leaks
  ~Bird() override;

 private:
};

#endif // ANGRYNERDS_BIRDS_H
