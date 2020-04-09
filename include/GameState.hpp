#pragma once
#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <sol.hpp>

namespace Skeleton {
class GameState : public State {

public:
  GameState(gameDataRef data);
  void init();
  void handleInput();
  void update(float dt);
  void draw();

private:
  gameDataRef data;
  sf::Sprite background;
  sol::state script;
  Entity redTank;
  EntityManager tanks;
  SystemManager systems;
};
} // namespace Skeleton