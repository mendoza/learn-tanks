#pragma once
#include <Engine.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <sol.hpp>

class GameState : public Skeleton::State {

public:
  GameState(Skeleton::gameDataRef data);
  void init();
  void handleInput();
  void update(float dt);
  void draw();

private:
  Skeleton::gameDataRef data;
  sf::Sprite background;
  sol::state script;
  Skeleton::Entity redTank;
  Skeleton::EntityManager tanks;
  Skeleton::SystemManager systems;
};