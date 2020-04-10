#pragma once
#include <Engine.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <sol.hpp>

namespace Skeleton {
class SplashState : public State {

public:
  SplashState(gameDataRef data);
  void init();
  void handleInput();
  void update(float dt);
  void draw();

private:
  gameDataRef data;
  sf::Clock clock;
  sf::Sprite background;
  sol::state script;
  sol::table meta;
  sol::table splash;
};
} // namespace Skeleton