#include <Components.hpp>
#include <GameState.hpp>
#include <Systems.hpp>

GameState::GameState(Skeleton::GameDataRef Data) : Systems(Tanks), Data(Data) {}

void GameState::init() {
	this->Script.script_file("scripts/RedTank.lua");
	sol::table Tank = this->Script["Tank"];
	this->RedTank = this->Tanks.create();
	this->RedTank.add<GraphicComponent>(this->Data, Tank["graphicComponent"]);
	this->RedTank.get<GraphicComponent>().Sprite.setPosition(200, 200);
	this->Systems.add<drawGraphicSystem>(this->Data);
}

void GameState::handleInput() {
	sf::Event event;
	while (this->Data->Window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->Data->Window.close();
		}
	}
}

void GameState::update(float dt) {
	this->Data->Window.clear(sf::Color(125, 125, 125));
	this->Systems.update(dt);
	this->RedTank.get<GraphicComponent>().Sprite.rotate(45);
}

void GameState::draw() { this->Data->Window.display(); }
