#pragma once
#include <Engine.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <sol.hpp>
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
	sol::state Script;
	Tank RedTank;
	ecs::EntityManager Tanks;
	ecs::SystemManager Systems;
};