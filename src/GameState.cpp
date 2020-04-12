#include <Components.hpp>
#include <GameState.hpp>
#include <Systems.hpp>

GameState::GameState(Skeleton::GameDataRef Data)
	: RedTankSystem(Tanks), BlueTankSystem(Tanks), Data(Data) {}

void GameState::init() {
	this->Script.script_file("scripts/RedTank.lua");
	sol::table Player = this->Script["Tank"];
	this->RedTank = this->Tanks.create<Tank>(
		this->Data, Player["graphicComponent"], "scripts/RedTank.lua", 0);

	this->RedTankSystem.add<GraphicSystem>(this->Data);
	this->RedTankSystem.add<LogicSystem>();
	this->RedTankSystem.add<MovableSystem>();
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
	if (turn)
		this->RedTankSystem.update(dt);
	else
		this->BlueTankSystem.update(dt);
	turn = !turn;
}

void GameState::draw() { this->Data->Window.display(); }
