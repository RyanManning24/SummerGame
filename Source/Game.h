#pragma once
#include <Engine/OGLGame.h>
#include <string>

#include "Birds.h"
#include "Components/GameObject.h"
#include "Pigs.h"
#include "Utility/Rect.h"

/**
 *  An OpenGL Game based on ASGE.
 */
class Angry : public ASGE::OGLGame
{
 public:
  Angry();
  ~Angry();
  virtual bool init() override;

 private:
  void keyHandler(const ASGE::SharedEventData data);
  void clickHandler(const ASGE::SharedEventData data);
  void setupResolution();
  bool loadBackgrounds();
  bool loadPlayer();
  bool loadEnemies();
  void BirdMovement(const ASGE::GameTime& game_time);
  void Gravity(const ASGE::GameTime& game_time);
  void Boundary();
  void Collision();
  void Playability();

  virtual void update(const ASGE::GameTime&) override;
  virtual void render(const ASGE::GameTime&) override;

  int key_callback_id = -1;   /**< Key Input Callback ID. */
  int mouse_callback_id = -1; /**< Mouse Input Callback ID. */

  // Add your GameObjects
  GameObject background_layer;
  GameObject menu_layer;

  Birds Player[3];
  Pigs Enemies[3];

  float Bird_Ypos = 0;
  float Bird_Xpos = 0;

  int Player_Count = -1;
  int Enemy_Count = 0;
  int Score = 0;

  int Switch = 0;
  double First_Click_X = 0;
  double First_Click_Y = 0;
  bool Mouse_is_pressed = false;
  bool Mouse_is_released = false;

  int Level_Select = 1;

  bool in_menu = true;
  int menu_Option = 0;
};