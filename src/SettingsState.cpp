#include <SettingsState.hpp>

SettingsState::SettingsState(Skeleton::GameDataRef data) : Data(data) {}

SettingsState::~SettingsState() {
	auto it = this->Buttons.begin();
	for (it = this->Buttons.begin(); it != this->Buttons.end(); ++it) {
		delete it->second;
	}
}

void SettingsState::init() {
	this->Buttons["MENU_STATE"] = new Skeleton::GUI::Button(
		Skeleton::GUI::p2pX(15.6f, &this->Data->Window),
		Skeleton::GUI::p2pY(30.f, &this->Data->Window),
		Skeleton::GUI::p2pX(13.f, &this->Data->Window),
		Skeleton::GUI::p2pY(6.f, &this->Data->Window), 0,
		&this->Data->Assets.getFont("GameFont"), "Go Back",
		Skeleton::GUI::calcCharSize(&this->Data->Window),
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0),
		&this->Data->Assets.getSound("hoverSound"),
		&this->Data->Assets.getSound("clickSound"));
}

void SettingsState::handleInput() {
	sf::Event event;
	while (this->Data->Window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->Data->Window.close();
		}
		if (this->Buttons["MENU_STATE"]->isPressed())
			this->Data->Machine.removeState();
	}
}

void SettingsState::update(float dt) {
	for (auto &it : this->Buttons) {
		it.second->update(sf::Mouse::getPosition(this->Data->Window));
	}
}

void SettingsState::draw() {
	this->Data->Window.clear(sf::Color(125, 125, 125));
	for (auto &it : this->Buttons) {
		this->Data->Window.draw(*it.second);
	}
	this->Data->Window.display();
}
