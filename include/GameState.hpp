#pragma once
#include <Engine.hpp>
#include <Tank.hpp>

class GameState : public Skeleton::State {

  public:
	GameState(Skeleton::GameDataRef Data);
	void init();
	void handleInput();
	void update(float dt);
	void draw();

  private:
	Skeleton::GameDataRef Data;
	sf::Sprite Background;
	sf::Clock Clock;
	bool turn;
	sol::state Script;
	Tank RedTank;
	Tank BlueTank;
	ecs::EntityManager Tanks;
	ecs::SystemManager GraphicsSystem;
	ecs::SystemManager OthersSystem;
};