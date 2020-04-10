#pragma once
#include <Engine.hpp>
#include <GUI.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <sol.hpp>

namespace Skeleton {
class MenuState : public State {

public:
  MenuState(gameDataRef data);
  ~MenuState();
  void init();
  void handleInput();
  void update(float dt);
  void draw();

private:
  gameDataRef data;
  std::map<std::string, GUI::Button *> buttons;
  sf::Sprite background;
};
} // namespace Skeleton