//
// Created by Ryanm on 17/05/2019.
//

#ifndef ANGRYNERDS_GAMELEVEL_H
#define ANGRYNERDS_GAMELEVEL_H

class GameLevel
{
 public:
  GameLevel();
  ~GameLevel();

 private:
  const int playerCount = 1;
  int EnemyCount = 0;
  int GameLevel = 0;
};

#endif // ANGRYNERDS_GAMELEVEL_H
