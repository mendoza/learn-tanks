#include <GUI.hpp>
#include <cmath>
#include <iostream>

namespace GUI {
const float p2pX(float perc, sf::RenderWindow *window) {
  return std::ceil(static_cast<float>(window->getSize().x) * (perc / 100.f));
}

const float p2pY(float perc, sf::RenderWindow *window) {
  return std::ceil(static_cast<float>(window->getSize().y) * (perc / 100.f));
}

const unsigned calcCharSize(sf::RenderWindow *window, const unsigned modifier) {
  return static_cast<unsigned>((window->getSize().x + window->getSize().y) /
                               modifier);
}

Button::Button(float x, float y, float w, float h, short unsigned id,
               sf::Font *font, std::string text, unsigned charSize,
               sf::Color text_idle, sf::Color text_hover, sf::Color text_active,
               sf::Color idle, sf::Color hover, sf::Color active,
               sf::Color outline_idle, sf::Color outline_hover,
               sf::Color outline_active)
    : Widget(id) {
  this->buttonState = BTN_IDLE;

  this->shape.setPosition(sf::Vector2f(x, y));
  this->shape.setSize(sf::Vector2f(w, h));
  this->shape.setFillColor(idle);
  this->shape.setOutlineThickness(1.f);
  this->shape.setOutlineColor(outline_idle);

  this->font = font;
  this->text.setFont(*this->font);
  this->text.setString(text);
  this->text.setFillColor(text_idle);
  this->text.setCharacterSize(charSize);
  this->text.setPosition(this->shape.getPosition().x +
                             (this->shape.getGlobalBounds().width / 2.f) -
                             this->text.getGlobalBounds().width / 2.f,
                         this->shape.getPosition().y);

  this->textIdleColor = text_idle;
  this->textHoverColor = text_hover;
  this->textActiveColor = text_active;

  this->idleColor = idle;
  this->hoverColor = hover;
  this->activeColor = active;

  this->outlineIdleColor = outline_idle;
  this->outlineHoverColor = outline_hover;
  this->outlineActiveColor = outline_active;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->shape, states);
  target.draw(this->text, states);
}

void Button::update(const sf::Vector2i mousePos) {
  this->buttonState = BTN_IDLE;
  sf::IntRect tempRect(this->shape.getPosition().x, this->shape.getPosition().y,
                       this->shape.getGlobalBounds().width,
                       this->shape.getGlobalBounds().height);
  if (tempRect.contains(mousePos)) {
    this->buttonState = BTN_HOVER;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      this->buttonState = BTN_ACTIVE;
    }
  }

  switch (this->buttonState) {
  case BTN_IDLE:
    this->shape.setFillColor(this->idleColor);
    this->text.setFillColor(this->textIdleColor);
    this->shape.setOutlineColor(this->outlineIdleColor);
    break;

  case BTN_HOVER:
    this->shape.setFillColor(this->hoverColor);
    this->text.setFillColor(this->textHoverColor);
    this->shape.setOutlineColor(this->outlineHoverColor);
    break;

  case BTN_ACTIVE:
    this->shape.setFillColor(this->activeColor);
    this->text.setFillColor(this->textActiveColor);
    this->shape.setOutlineColor(this->outlineActiveColor);
    break;

  default:
    this->shape.setFillColor(sf::Color::Red);
    this->text.setFillColor(sf::Color::Blue);
    this->shape.setOutlineColor(sf::Color::Green);
    break;
  }
}

const bool Button::isPressed() const { return this->buttonState == BTN_ACTIVE; }

TextField::TextField(float x, float y, float w, float h, short unsigned id,
                     sf::Font *font, std::string text, unsigned charSize,
                     sf::Color textColor, sf::Color shapeColor,
                     sf::Color outlineColor)
    : Widget(id) {
  this->shape.setPosition(sf::Vector2f(x, y));
  this->shape.setSize(sf::Vector2f(w, h));
  this->shape.setFillColor(shapeColor);
  this->shape.setOutlineThickness(1.f);
  this->shape.setOutlineColor(outlineColor);

  this->font = font;
  this->text.setFont(*this->font);
  this->text.setString(text);
  this->text.setFillColor(textColor);
  this->text.setCharacterSize(charSize);
  this->text.setPosition(this->shape.getPosition().x -
                             this->text.getGlobalBounds().width / 2.f,
                         this->shape.getPosition().y);

  this->textColor = textColor;
  this->shapeColor = shapeColor;
  this->outlineColor = outlineColor;
}

void TextField::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->shape, states);
  target.draw(this->text, states);
}

void TextField::update(sf::Event event) {
  if (sf::Event::TextEntered == event.type &&
      (this->text.getGlobalBounds().width <=
           this->shape.getGlobalBounds().width ||
       event.text.unicode == '\b')) {
    std::string str = this->text.getString();
    if (event.text.unicode == '\b')
      str = str.substr(0, str.size() - 1);
    else if (event.text.unicode < 128)
      str += static_cast<char>(event.text.unicode);
    this->setText(str);
  }
}
std::string TextField::getText() { return this->text.getString(); }

void TextField::setText(std::string text) { this->text.setString(text); }
} // namespace GUI