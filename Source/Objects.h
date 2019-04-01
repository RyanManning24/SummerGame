//
// Created by Ryanm on 01/04/2019.
//

#ifndef ANGRYNERDS_OBJECTS_H
#define ANGRYNERDS_OBJECTS_H

class Objects
{
 public:
  Objects();
  ~Objects();

 private:
  void LoadSprite();
  void free();

  int Times_hit = 0;
  int Number_Of_Objects = 0;
};

#endif // ANGRYNERDS_OBJECTS_H
