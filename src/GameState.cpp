#include <Components.hpp>
#include <GameState.hpp>
#include <Systems.hpp>

namespace Skeleton {
GameState::GameState(gameDataRef data) : systems(tanks) {
  this->_data = data;
  this->script.script_file("scripts/RedTank.lua");
  sol::table player = this->script["Tank"];
  this->redTank = this->tanks.create();
  this->redTank.add<GraphicComponent>(this->_data, player["graphicComponent"]);
  this->systems.add<drawGraphicSystem>(this->_data);
}
// GameState::~GameState() { }
void GameState::init() {}

void GameState::handleInput() {
  sf::Event event;
  while (this->_data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      this->_data->window.close();
    }
  }
}

void GameState::update(float dt) {
  this->_data->window.clear(sf::Color(125, 125, 125));
  this->systems.update(dt);
}

void GameState::draw() { this->_data->window.display(); }
} // namespace Skeleton