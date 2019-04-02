#include "GameObject.h"
#include <Engine/Renderer.h>

GameObject::~GameObject()
{
  free();
}

bool GameObject::addSpriteComponent(ASGE::Renderer* renderer,
                                    const std::string& texture_file_name)
{
  free();

  sprite_component = new SpriteComponent();
  if (sprite_component->loadSprite(renderer, texture_file_name))
  {
    return true;
  }

  free();
  return false;
}

void GameObject::free()
{
  delete sprite_component;
  sprite_component = nullptr;
}

SpriteComponent* GameObject::spriteComponent()
{
  return sprite_component;
}

bool GameObject::Get_Visibility()
{
  return Visibility;
}
void GameObject::Set_Visibility(bool SetVisiblity)
{
  Visibility = SetVisiblity;
}

vector2 GameObject::Get_Velocity()
{
  return Velocity;
}

void GameObject::Set_Velocity(float VectorX, float VectorY)
{
  Velocity = vector2(VectorX, VectorY);
}

float GameObject::Get_Speed()
{
  return Speed;
}

void GameObject::Set_Speed(float SetSpeed)
{
  Speed = SetSpeed;
}