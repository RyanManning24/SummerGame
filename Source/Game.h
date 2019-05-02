#pragma once
#include <Engine/OGLGame.h>
#include <string>

#include "Bird.h"
#include "Components/GameObject.h"
#include "Pig.h"
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

  //@Feedbac: you've completed ignored the coding standards
  Bird players[3];
  Pig enemies[3];

  //@Feedback: why isn't this in the bird class :confused:?
  float Bird_Ypos = 0;
  float Bird_Xpos = 0;

  int player_count = -1;
  int enemy_count = 0;
  int score = 0;

  int Switch = 0;
  double First_Click_X = 0;
  double First_Click_Y = 0;

  //@Feedback: if the mouse isn't pressed you can work out if it's released
  // without using a second variable.
  // if mouse_event == released && mouse_pressed then set to false
  bool mouse_pressed = false;
  bool mouse_released = false;

  //@Feedback: consider a level class or a game state system
  int Level_Select = 1;
  bool in_menu = true;
  int menu_Option = 0;

  void handleLevel10(const ASGE::KeyEvent* key);

  void handleOption10(const ASGE::KeyEvent* key);

  void handleMenu(const ASGE::KeyEvent* key);
};