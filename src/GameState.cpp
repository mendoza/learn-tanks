#include <Components.hpp>
#include <GameState.hpp>
#include <Systems.hpp>

GameState::GameState(Skeleton::gameDataRef data) : systems(tanks) {
  this->data = data;
  this->script.script_file("scripts/RedTank.lua");
}

void GameState::init() {
  sol::table player = this->script["Tank"];
  this->redTank = this->tanks.create();
  this->redTank.add<GraphicComponent>(this->data, player["graphicComponent"]);
  this->redTank.get<GraphicComponent>().sprite.setPosition(200, 200);
  this->systems.add<drawGraphicSystem>(this->data);
}

void GameState::handleInput() {
  sf::Event event;
  while (this->data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      this->data->window.close();
    }
  }
}

void GameState::update(float dt) {
  this->data->window.clear(sf::Color(125, 125, 125));
  this->systems.update(dt);
  this->redTank.get<GraphicComponent>().sprite.rotate(45);
}

void GameState::draw() { this->data->window.display(); }
