#pragma once
#include <Engine.hpp>
#include <GUI.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <sol.hpp>

class SettingsState : public Skeleton::State {

  public:
	SettingsState(Skeleton::GameDataRef data);
	~SettingsState();
	void init();
	void handleInput();
	void update(float dt);
	void draw();

  private:
	Skeleton::GameDataRef Data;
	std::map<std::string, Skeleton::GUI::Button *> Buttons;
};