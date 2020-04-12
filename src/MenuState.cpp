#include <Components.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <SettingsState.hpp>
#include <Systems.hpp>

MenuState::MenuState(Skeleton::GameDataRef data) : Data(data) {}

void MenuState::init() {
	this->Data->Assets.loadFont("GameFont", "assets/Fonts/arial.ttf");
	this->Data->Assets.loadSound("hoverSound", "assets/Sounds/hover.wav");
	this->Data->Assets.loadSound("clickSound", "assets/Sounds/click.wav");

	this->Buttons["GAME_STATE"] = new Skeleton::GUI::Button(
		Skeleton::GUI::p2pX(15.6f, &this->Data->Window),
		Skeleton::GUI::p2pY(30.f, &this->Data->Window),
		Skeleton::GUI::p2pX(13.f, &this->Data->Window),
		Skeleton::GUI::p2pY(6.f, &this->Data->Window), 0,
		&this->Data->Assets.getFont("GameFont"), "Start Game",
		Skeleton::GUI::calcCharSize(&this->Data->Window),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0),
		&this->Data->Assets.getSound("hoverSound"),
		&this->Data->Assets.getSound("clickSound"), sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->Buttons["SETTINGS_STATE"] = new Skeleton::GUI::Button(
		Skeleton::GUI::p2pX(15.6f, &this->Data->Window),
		Skeleton::GUI::p2pY(40.f, &this->Data->Window),
		Skeleton::GUI::p2pX(13.f, &this->Data->Window),
		Skeleton::GUI::p2pY(6.f, &this->Data->Window), 1,
		&this->Data->Assets.getFont("GameFont"), "Settings",
		Skeleton::GUI::calcCharSize(&this->Data->Window),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		&this->Data->Assets.getSound("hoverSound"),
		&this->Data->Assets.getSound("clickSound"));

	this->Buttons["EXIT_STATE"] = new Skeleton::GUI::Button(
		Skeleton::GUI::p2pX(15.6f, &this->Data->Window),
		Skeleton::GUI::p2pY(50.f, &this->Data->Window),
		Skeleton::GUI::p2pX(13.f, &this->Data->Window),
		Skeleton::GUI::p2pY(6.f, &this->Data->Window), 2,
		&this->Data->Assets.getFont("GameFont"), "Quit",
		Skeleton::GUI::calcCharSize(&this->Data->Window),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 50), sf::Color(100, 100, 100, 0),
		sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		&this->Data->Assets.getSound("hoverSound"),
		&this->Data->Assets.getSound("clickSound"));
}

MenuState::~MenuState() {
	auto it = this->Buttons.begin();
	for (it = this->Buttons.begin(); it != this->Buttons.end(); ++it) {
		delete it->second;
	}
}

void MenuState::handleInput() {
	sf::Event event;
	while (this->Data->Window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->Data->Window.close();
		}
		if (this->Buttons["GAME_STATE"]->isPressed())
			this->Data->Machine.addState(
				Skeleton::StateRef(new GameState(this->Data)));

		if (this->Buttons["SETTINGS_STATE"]->isPressed())
			this->Data->Machine.addState(
				Skeleton::StateRef(new SettingsState(this->Data)), false);

		if (this->Buttons["EXIT_STATE"]->isPressed())
			this->Data->Window.close();
	}
}

void MenuState::update(float dt) {
	for (auto &it : this->Buttons) {
		it.second->update(sf::Mouse::getPosition(this->Data->Window));
	}
}

void MenuState::draw() {
	this->Data->Window.clear(sf::Color(125, 125, 125));
	for (auto &it : this->Buttons) {
		this->Data->Window.draw(*it.second);
	}
	this->Data->Window.display();
}