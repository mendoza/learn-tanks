#include <Components.hpp>
#include <GameState.hpp>
#include <MenuState.hpp>
#include <Systems.hpp>

namespace Skeleton {
MenuState::MenuState(gameDataRef data) { this->data = data; }
// MenuState::~MenuState() { }
void MenuState::init() {
  this->data->assets.loadTexture("button", "assets/Sprites/Button.png");
  this->startButton.setTexture(this->data->assets.getTexture("button"));
  sf::Vector2u windowSize = this->data->window.getSize();
  sf::Vector2f startButtonPosition = {
      (windowSize.x / 2.f) - (this->startButton.getGlobalBounds().width / 2),
      (windowSize.y / 2.f) - (this->startButton.getGlobalBounds().height / 2)};

  this->startButton.setPosition(startButtonPosition);

  this->rectangle.setSize(
      sf::Vector2f(this->data->assets.getTexture("button").getSize().x,
                   this->data->assets.getTexture("button").getSize().y));
  this->rectangle.setOutlineColor(sf::Color::Red);
  this->rectangle.setOutlineThickness(5);
  this->rectangle.setPosition(this->startButton.getPosition());
}

void MenuState::handleInput() {
  sf::Event event;
  while (this->data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      this->data->window.close();
    }
    if (this->data->input.isSpriteClicked(this->startButton, sf::Mouse::Left,
                                          this->data->window)) {
      this->data->machine.addState(StateRef(new GameState(this->data)));
    }
  }
}

void MenuState::update(float dt) {}

void MenuState::draw() {
  this->data->window.clear(sf::Color(125, 125, 125));
  this->data->window.draw(this->rectangle);
  this->data->window.draw(this->startButton);
  this->data->window.display();
}
} // namespace Skeleton