//
// Created by Ryanm on 01/04/2019.
//

#ifndef ANGRYNERDS_PIG_H
#define ANGRYNERDS_PIG_H

#include "Components/GameObject.h"

//@Feedback: this class is not needed
class Pig : public GameObject
{
 public:
  Pig();
  ~Pig() override;

 private:
  //@Feedback: pigs should not know about the game, that's the game's job to
  // know how many pigs remain.
  int Pigs_Left = 2;
};

#endif // ANGRYNERDS_PIG_H
