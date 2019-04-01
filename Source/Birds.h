//
// Created by Ryanm on 01/04/2019.
//

#ifndef ANGRYNERDS_BIRDS_H
#define ANGRYNERDS_BIRDS_H

class Birds
{
 public:
  Birds();
  ~Birds();

 private:
  float BirdsMovement();
  void LoadSprite();
  void free();
};

#endif // ANGRYNERDS_BIRDS_H
