#include <string>

#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>
#include <iostream>

#include "Birds.h"
#include "Game.h"

/**
*   @brief   Default Constructor.
*   @details Consider setting the game's width and height
             and even seeding the random number generator.
*/
Angry::Angry()
{
  std::srand(static_cast<unsigned int>(time(nullptr)));
}

/**
 *   @brief   Destructor.
 *   @details Remove any non-managed memory and callbacks.
 */
Angry::~Angry()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
  this->inputs->unregisterCallback(
    static_cast<unsigned int>(mouse_callback_id));
}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
                         run the game are loaded. The keyHandler and
clickHandler callback should also be set in the initialise function.
*   @return  True if the game initialised correctly.
*/

bool Angry::loadPlayer()
{
  float Player_X = 0;
  float Player_Start_Y = 750;

  for (int i = 0; i < 3; i++)
  {
    if (Player[i].addSpriteComponent(renderer.get(),
                                     "data/Textures/chicken.png"))
    {
      Player_Count++;
      float Player_Width = Player->spriteComponent()->getSprite()->width();
      Player_X += Player_Width;
      Player[i].spriteComponent()->getSprite()->xPos(Player_X);
      Player[i].spriteComponent()->getSprite()->yPos(Player_Start_Y);
    }
    else
    {
      return false;
    }
  }
  return true;
}

bool Angry::loadEnemies()
{
  float Enemies_Start_Y = 760;
  float Enemy_X = static_cast<float>(game_width);

  for (int i = 0; i < 3; i++)
  {
    if (Enemies[i].addSpriteComponent(renderer.get(),
                                      "/data/Textures/crocodile.png"))
    {
      float Enemies_Width =
        Enemies[i].spriteComponent()->getSprite()->width() + 100;
      Enemy_X -= Enemies_Width;
      Enemies[i].spriteComponent()->getSprite()->yPos(Enemies_Start_Y);
      Enemies[i].spriteComponent()->getSprite()->xPos(Enemy_X);
      Enemy_Count++;
    }
    else
    {
      return false;
    }
  }
  return true;
}

bool Angry::init()
{
  setupResolution();
  if (!initAPI())
  {
    return false;
  }

  toggleFPS();
  renderer->setWindowTitle("Angry Birds!");
  renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
  renderer->setClearColour(ASGE::COLOURS::BLACK);

  // input handling functions
  inputs->use_threads = false;

  key_callback_id =
    inputs->addCallbackFnc(ASGE::E_KEY, &Angry::keyHandler, this);

  mouse_callback_id =
    inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &Angry::clickHandler, this);

  if (!loadPlayer())
  {
    return false;
  }
  if (!loadEnemies())
  {
    return false;
  }
  if (!loadBackgrounds())
  {
    return false;
  }

  if (!menu_layer.addSpriteComponent(renderer.get(),
                                     "data/Textures/Backdrops/menu.jpg"))
  {
    return false;
  }

  return true;
}

bool Angry::loadBackgrounds()
{
  std::string filename = "data/Textures/Backdrops/lvl";
  filename += std::to_string(std::rand() % 3 + 1);
  filename += ".png";

  if (!background_layer.addSpriteComponent(renderer.get(), filename))
  {
    return false;
  }

  return true;
}

/**
*   @brief   Sets the game window resolution
*   @details This function is designed to create the window size, any
             aspect ratio scaling factors and safe zones to ensure the
                         game frames when resolutions are changed in size.
*   @return  void
*/
void Angry::setupResolution()
{
  // how will you calculate the game's resolution?
  // will it scale correctly in full screen? what AR will you use?
  // how will the game be framed in native 16:9 resolutions?
  // here are some abritrary values for you to adjust as you see fit
  // https://tinyurl.com/y6sqbr78
  game_width = 1920;
  game_height = 1080;
}

/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
                         keyboard input. For this game, calls to this function
                         are thread safe, so you may alter the game's state as
you see fit.
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void Angry::keyHandler(const ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }

  else if (key->key == ASGE::KEYS::KEY_ENTER &&
           key->action == ASGE::KEYS::KEY_PRESSED && key->mods == 0x0004)
  {
    if (renderer->getWindowMode() == ASGE::Renderer::WindowMode::WINDOWED)
    {
      renderer->setWindowedMode(ASGE::Renderer::WindowMode::FULLSCREEN);
    }
    else
    {
      renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
    }
  }

  else if (in_menu)
  {
    if (key->key == ASGE::KEYS::KEY_SPACE)
    {
      in_menu = !in_menu;
    }

    if (key->key == ASGE::KEYS::KEY_DOWN &&
        key->action == ASGE::KEYS::KEY_RELEASED)
    {
      Level_Select++;
    }
    if (key->key == ASGE::KEYS::KEY_UP &&
        key->action == ASGE::KEYS::KEY_RELEASED)
    {
      Level_Select--;
    }

    if (Level_Select == 3)
    {
      Level_Select = 1;
    }

    if (menu_Option == 10)
    {
      if (key->key == ASGE::KEYS::KEY_ENTER &&
          key->action == ASGE::KEYS::KEY_RELEASED)
      {
        menu_Option = 0;
      }
    }
    if (menu_Option == 20)
    {
      if (key->key == ASGE::KEYS::KEY_ENTER &&
          key->action == ASGE::KEYS::KEY_RELEASED)
      {
        menu_Option = 0;
      }
    }
  }
}

/**
*   @brief   Processes any click inputs
*   @details This function is added as a callback to handle the game's
                     mouse button input. For this game, calls to this function
             are thread safe, so you may alter the game's state as you
             see fit.
*   @param   data The event data relating to key input.
*   @see     ClickEvent
*   @return  void
*/
void Angry::clickHandler(const ASGE::SharedEventData data)
{
  auto click = static_cast<const ASGE::ClickEvent*>(data.get());
  double x_pos = click->xpos;
  double y_pos = click->ypos;

  if (Switch % 2 == 0)
  {
    Mouse_is_released = false;
    Mouse_is_pressed = true;
    First_Click_X = x_pos;
    First_Click_Y = y_pos;
    Switch++;
  }
  else if (Switch % 2 == 1)
  {
    Mouse_is_released = true;
    Mouse_is_pressed = false;
    First_Click_X -= x_pos;
    First_Click_Y -= y_pos;
    Player[Player_Count].Set_Velocity(static_cast<float>(First_Click_X) / 100,
                                      static_cast<float>(First_Click_Y) / 100);
    Player[Player_Count].Get_Velocity().normalise();
    Switch = 0;
  }
}

void Angry::BirdMovement(const ASGE::GameTime& game_time)
{
  auto dt_sec = game_time.delta.count() / 1000.0;
  if (Mouse_is_released)
  {
    Player[Player_Count].Set_Speed(1);

    Bird_Xpos = Player[Player_Count].spriteComponent()->getSprite()->xPos();
    Bird_Ypos = Player[Player_Count].spriteComponent()->getSprite()->yPos();
    Bird_Xpos +=
      Player[Player_Count].Get_Velocity().x *
      (Player[Player_Count].Get_Speed() * static_cast<float>(dt_sec));
    Bird_Ypos +=
      Player[Player_Count].Get_Velocity().y *
      (Player[Player_Count].Get_Speed() * static_cast<float>(dt_sec));
    Player[Player_Count].spriteComponent()->getSprite()->xPos(Bird_Xpos);
    Player[Player_Count].spriteComponent()->getSprite()->yPos(Bird_Ypos);
  }
}

void Angry::Gravity(const ASGE::GameTime& game_time)
{
  auto dt_sec = game_time.delta.count() / 1000.0;
  const float gravity = 0.002f;
  if (Player[Player_Count].Get_Visability() &&
      Player[Player_Count].Get_Velocity().x != 0 &&
      Player[Player_Count].Get_Velocity().y != 0)
  {
    Bird_Ypos = Player[Player_Count].spriteComponent()->getSprite()->yPos();
    Player[Player_Count].Set_Velocity(Player[Player_Count].Get_Velocity().x,
                                      Player[Player_Count].Get_Velocity().y +
                                        gravity);
    Bird_Ypos -=
      Player[Player_Count].Get_Velocity().y * static_cast<float>(dt_sec);
    Player[Player_Count].spriteComponent()->getSprite()->yPos(Bird_Ypos);
  }
}

void Angry::Boundary()
{
  if (Player[Player_Count].spriteComponent()->getSprite()->xPos() >=
      static_cast<float>(game_width))
  {
    Player[Player_Count].Set_Visability(false);
    Player_Count--;
    Mouse_is_released = false;
    Mouse_is_pressed = false;
  }
  else if (Player[Player_Count].spriteComponent()->getSprite()->yPos() >= 850)
  {
    Player[Player_Count].Set_Visability(false);
    Player_Count--;
    Mouse_is_released = false;
    Mouse_is_pressed = false;
  }
}
void Angry::Playability()
{
  if (Enemy_Count == 0)
  {
    in_menu = true;
    menu_Option = 20;
    Score = 0;
    Enemy_Count = 3;
    loadPlayer();
    loadEnemies();
    for (int i = 0; i < 3; i++)
    {
      Enemies[i].Set_Visability(true);
      Player[i].Set_Visability(true);
      Player[i].Set_Velocity(0, 0);
    }
  }
  else if (Player_Count == -1)
  {
    in_menu = true;
    menu_Option = 10;
    Score = 0;
    Enemy_Count = 0;
    loadPlayer();
    loadEnemies();
    for (int i = 0; i < 3; i++)
    {
      Player[i].Set_Visability(true);
      Enemies[i].Set_Visability(true);
      Player[i].Set_Velocity(0, 0);
    }
  }
}

void Angry::Collision()
{
  for (int i = 0; i < 3; i++)
  {
    if (Player[Player_Count].Get_Visability() && Enemies[i].Get_Visability())
    {
      if (Player[Player_Count].spriteComponent()->getBoundingBox().isInside(
            Enemies[i].spriteComponent()->getBoundingBox()))
      {
        Enemies[i].Set_Visability(false);
        Player[Player_Count].Set_Visability(false);
        Score += 10;
        Enemy_Count--;
        Player_Count--;
        Player[Player_Count].Set_Velocity(0, 0);
      }
    }
  }
}
/**Collision();
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
                     current frame. Once the current frame is has finished
                     the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void Angry::update(const ASGE::GameTime& game_time)
{
  // make sure you use delta time in any movement calculations!
  // auto dt_sec = game_time.delta.count() / 1000.0;

  if (!in_menu)
  {
    Playability();
    BirdMovement(game_time);
    Collision();
    if (Mouse_is_released)
    {
      Gravity(game_time);
      Boundary();
    }
  }
}

/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
                 Once the current frame is has finished the buffers are
                         swapped accordingly and the image shown.
*   @return  void
*/
void Angry::render(const ASGE::GameTime& game_time)
{
  renderer->setFont(0);

  if (in_menu)
  {
    if (menu_Option == 0)
    {
      renderer->renderSprite(*menu_layer.spriteComponent()->getSprite());

      renderer->renderText("Press space to start and to pick a level!",
                           200,
                           150,
                           3,
                           ASGE::COLOURS::BLACK);
      renderer->renderText("Use the arrow keys to navigate the menu!",
                           200,
                           250,
                           3,
                           ASGE::COLOURS::BLACK);

      renderer->renderText(Level_Select == 1 ? ">Level 1" : "Level 1",
                           350,
                           450,
                           2,
                           ASGE::COLOURS::BLACK);
      renderer->renderText(Level_Select == 2 ? ">Level 2" : "Level 2",
                           350,
                           650,
                           2,
                           ASGE::COLOURS::BLACK);
    }
    if (menu_Option == 10)
    {
      renderer->renderSprite(*menu_layer.spriteComponent()->getSprite());
      renderer->renderText("You Lost!!", 700, 100, 3, ASGE::COLOURS::BLACK);
      renderer->renderText(
        "Press Enter to go back to menu", 400, 850, 3, ASGE::COLOURS::BLACK);
    }
    if (menu_Option == 20)
    {
      renderer->renderSprite(*menu_layer.spriteComponent()->getSprite());
      renderer->renderText("You WiN", 700, 100, 3, ASGE::COLOURS::BLACK);
      renderer->renderText(
        "Press Enter to go back to menu", 400, 850, 3, ASGE::COLOURS::BLACK);
    }
  }
  else
  {
    renderer->renderSprite(*background_layer.spriteComponent()->getSprite());
    std::string Score_str = "Score: " + std::to_string(Score);
    renderer->renderText(
      Score_str.c_str(), game_width - 150, 40, 1.0, ASGE::COLOURS::BLACK);
    std::string Chicken_str =
      "Chicken's Remaining " + std::to_string(Player_Count);
    renderer->renderText(
      Chicken_str.c_str(), 150, 40, 1.0, ASGE::COLOURS::BLACK);

    if (Level_Select == 1)
    {
      for (int i = 0; i < 3; i++)
      {
        if (Player[i].Get_Visability())
        {
          renderer->renderSprite(*Player[i].spriteComponent()->getSprite());
        }
      }
      for (int j = 0; j < 3; j++)
      {
        if (Enemies[j].Get_Visability())
        {
          renderer->renderSprite(*Enemies[j].spriteComponent()->getSprite());
        }
      }
    }
  }
}
