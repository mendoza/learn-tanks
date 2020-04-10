#pragma once
#include <Engine.hpp>
#include <GUI.hpp>
#include <SFML/Graphics.hpp>
#include <sol.hpp>

class MenuState : public Skeleton::State {

public:
  MenuState(Skeleton::gameDataRef data);
  ~MenuState();
  void init();
  void handleInput();
  void update(float dt);
  void draw();

private:
  Skeleton::gameDataRef data;
  std::map<std::string, Skeleton::GUI::Button *> buttons;
  sf::Sprite background;
};