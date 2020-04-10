#include <Components.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <SettingsState.hpp>
#include <Systems.hpp>

MenuState::MenuState(Skeleton::gameDataRef data) : data(data) {}

void MenuState::init() {
  this->data->assets.loadFont("GameFont", "assets/Fonts/ARCADECLASSIC.TTF");
  this->data->assets.loadSound("hoverSound", "assets/Sounds/hover.wav");
  this->data->assets.loadSound("clickSound", "assets/Sounds/click.wav");

  this->buttons["GAME_STATE"] = new Skeleton::GUI::Button(
      Skeleton::GUI::p2pX(15.6f, &this->data->window),
      Skeleton::GUI::p2pY(30.f, &this->data->window),
      Skeleton::GUI::p2pX(13.f, &this->data->window),
      Skeleton::GUI::p2pY(6.f, &this->data->window), 0,
      &this->data->assets.getFont("GameFont"), "Start Game",
      Skeleton::GUI::calcCharSize(&this->data->window),
      sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255),
      sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 0),
      sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0),
      &this->data->assets.getSound("hoverSound"),
      &this->data->assets.getSound("clickSound"));

  this->buttons["SETTINGS_STATE"] = new Skeleton::GUI::Button(
      Skeleton::GUI::p2pX(15.6f, &this->data->window),
      Skeleton::GUI::p2pY(40.f, &this->data->window),
      Skeleton::GUI::p2pX(13.f, &this->data->window),
      Skeleton::GUI::p2pY(6.f, &this->data->window), 1,
      &this->data->assets.getFont("GameFont"), "Settings",
      Skeleton::GUI::calcCharSize(&this->data->window),
      sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255),
      sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0),
      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
      &this->data->assets.getSound("hoverSound"),
      &this->data->assets.getSound("clickSound"));

  this->buttons["EXIT_STATE"] = new Skeleton::GUI::Button(
      Skeleton::GUI::p2pX(15.6f, &this->data->window),
      Skeleton::GUI::p2pY(50.f, &this->data->window),
      Skeleton::GUI::p2pX(13.f, &this->data->window),
      Skeleton::GUI::p2pY(6.f, &this->data->window), 2,
      &this->data->assets.getFont("GameFont"), "Quit",
      Skeleton::GUI::calcCharSize(&this->data->window),
      sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255),
      sf::Color(20, 20, 20, 50), sf::Color(100, 100, 100, 0),
      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
      &this->data->assets.getSound("hoverSound"),
      &this->data->assets.getSound("clickSound"));
}

MenuState::~MenuState() {
  auto it = this->buttons.begin();
  for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }
}

void MenuState::handleInput() {
  sf::Event event;
  while (this->data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      this->data->window.close();
    }
    if (this->buttons["GAME_STATE"]->isPressed())
      this->data->machine.addState(
          Skeleton::StateRef(new GameState(this->data)));

    if (this->buttons["SETTINGS_STATE"]->isPressed())
      this->data->machine.addState(
          Skeleton::StateRef(new SettingsState(this->data)), false);

    if (this->buttons["EXIT_STATE"]->isPressed())
      this->data->window.close();
  }
}

void MenuState::update(float dt) {
  for (auto &it : this->buttons) {
    it.second->update(sf::Mouse::getPosition(this->data->window));
  }
}

void MenuState::draw() {
  this->data->window.clear(sf::Color(125, 125, 125));
  for (auto &it : this->buttons) {
    this->data->window.draw(*it.second);
  }
  this->data->window.display();
}