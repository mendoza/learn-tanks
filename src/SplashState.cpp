#include <MenuState.hpp>
#include <SplashState.hpp>
#include <iostream>

namespace Skeleton {
SplashState::SplashState(gameDataRef data) : data(data) {
  this->script.script_file("scripts/MetaData.lua");
  this->meta = script["MetaData"];
  this->splash = script["MetaData"]["splash"];
}

void SplashState::init() {
  std::string filePath = this->splash["backgroundImageFile"];
  this->data->assets.loadTexture("Splash State Background", filePath);
  this->background.setTexture(
      this->data->assets.getTexture("Splash State Background"));
}

void SplashState::handleInput() {
  sf::Event event;
  while (this->data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      this->data->window.close();
    }
  }
}

void SplashState::update(float dt) {
  float time = this->splash["time"];
  if (this->clock.getElapsedTime().asSeconds() > time) {
    this->data->machine.addState(StateRef(new MenuState(this->data)));
  }
}

void SplashState::draw() {
  int r = this->splash["background"]["r"];
  int g = this->splash["background"]["g"];
  int b = this->splash["background"]["b"];
  this->data->window.clear(sf::Color(r, g, b));
  this->data->window.draw(this->background);
  this->data->window.display();
}
} // namespace Skeleton