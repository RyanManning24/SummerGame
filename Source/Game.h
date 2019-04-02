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

  virtual void update(const ASGE::GameTime&) override;
  virtual void render(const ASGE::GameTime&) override;

  int key_callback_id = -1;   /**< Key Input Callback ID. */
  int mouse_callback_id = -1; /**< Mouse Input Callback ID. */

  // Add your GameObjects
  GameObject background_layer;
  GameObject menu_layer;

  Birds Player[3];
  Pigs Enemies[3];

  int Level_Select = 0;

  bool in_menu = true;
};