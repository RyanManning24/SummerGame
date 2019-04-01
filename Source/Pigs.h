//
// Created by Ryanm on 01/04/2019.
//

#ifndef ANGRYNERDS_PIGS_H
#define ANGRYNERDS_PIGS_H

class Pigs
{
 public:
  Pigs();
  ~Pigs();

 private:
  void LoadSprite();
  void free();

  int Pigs_Left = 2;
};

#endif // ANGRYNERDS_PIGS_H
