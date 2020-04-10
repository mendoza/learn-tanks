#include <SettingsState.hpp>

SettingsState::SettingsState(Skeleton::gameDataRef data) : data(data) {}

SettingsState::~SettingsState() {
  auto it = this->buttons.begin();
  for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }
}

void SettingsState::init() {
  this->buttons["MENU_STATE"] = new Skeleton::GUI::Button(
      Skeleton::GUI::p2pX(15.6f, &this->data->window),
      Skeleton::GUI::p2pY(30.f, &this->data->window),
      Skeleton::GUI::p2pX(13.f, &this->data->window), Skeleton::GUI::p2pY(6.f, &this->data->window),
      0, &this->data->assets.getFont("GameFont"), "Go Back",
      Skeleton::GUI::calcCharSize(&this->data->window), sf::Color(200, 200, 200, 200),
      sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
      sf::Color(20, 20, 20, 0), sf::Color(70, 70, 70, 0),
      sf::Color(150, 150, 150, 0), &this->data->assets.getSound("hoverSound"),
      &this->data->assets.getSound("clickSound"));
}

void SettingsState::handleInput() {
  sf::Event event;
  while (this->data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      this->data->window.close();
    }
    if (this->buttons["MENU_STATE"]->isPressed())
      this->data->machine.removeState();
  }
}

void SettingsState::update(float dt) {
  for (auto &it : this->buttons) {
    it.second->update(sf::Mouse::getPosition(this->data->window));
  }
}

void SettingsState::draw() {
  this->data->window.clear(sf::Color(125, 125, 125));
  for (auto &it : this->buttons) {
    this->data->window.draw(*it.second);
  }
  this->data->window.display();
}
