#pragma once
#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <sol.hpp>

namespace Skeleton {
class MenuState : public State {

public:
  MenuState(gameDataRef data);
  void init();
  void handleInput();
  void update(float dt);
  void draw();

private:
  gameDataRef data;
  sf::Sprite background;
  sf::Sprite startButton;
  sf::RectangleShape rectangle;
};
} // namespace Skeleton