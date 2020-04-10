#pragma once
#include <Engine.hpp>
#include <GUI.hpp>
#include <SFML/Graphics.hpp>
#include <sol.hpp>

class MenuState : public Skeleton::State {
  public:
	MenuState(Skeleton::GameDataRef Data);
	~MenuState();
	void init();
	void handleInput();
	void update(float dt);
	void draw();

  private:
	Skeleton::GameDataRef Data;
	std::map<std::string, Skeleton::GUI::Button *> Buttons;
	sf::Sprite Background;
};