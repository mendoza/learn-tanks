#pragma once
#include <Engine.hpp>
#include <SFML/Graphics.hpp>
#include <sol.hpp>

class SplashState : public Skeleton::State {

public:
  SplashState(Skeleton::gameDataRef data);
  void init();
  void handleInput();
  void update(float dt);
  void draw();

private:
  Skeleton::gameDataRef data;
  sf::Clock clock;
  sf::Sprite background;
  sol::state script;
  sol::table meta;
  sol::table splash;
};