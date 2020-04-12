#pragma once
#include <Engine.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <Tank.hpp>
#include <sol.hpp>

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
	ecs::EntityManager Tanks;
	ecs::SystemManager RedTankSystem;
	ecs::SystemManager BlueTankSystem;
};