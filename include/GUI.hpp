#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
namespace Skeleton {
namespace GUI {
enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };
const float p2pX(float perc, sf::RenderWindow *window);
const float p2pY(float perc, sf::RenderWindow *window);
const unsigned calcCharSize(sf::RenderWindow *window,
                            const unsigned modifier = 60);

class Widget : public sf::Drawable {
public:
  Widget(short unsigned id) { this->id = id; }
  ~Widget() {}

private:
  short unsigned id;
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {}
  virtual void update() {}
};

class Button : public Widget {
  short unsigned buttonState;

public:
  Button(float x, float y, float w, float h, short unsigned id, sf::Font *font,
         std::string text, unsigned charSize, sf::Color text_idle,
         sf::Color text_hover, sf::Color text_active, sf::Color idle,
         sf::Color hover, sf::Color active, sf::SoundBuffer *hoverSound,
         sf::SoundBuffer *click,
         sf::Color outline_idle = sf::Color::Transparent,
         sf::Color outline_hover = sf::Color::Transparent,
         sf::Color outline_active = sf::Color::Transparent);
  ~Button() { delete this->font; }
  virtual void update(const sf::Vector2i mousePos);
  const bool isPressed() const;

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  bool hasPlayed;

  sf::RectangleShape shape;
  sf::Font *font;
  sf::Text text;

  sf::Color textIdleColor;
  sf::Color textHoverColor;
  sf::Color textActiveColor;

  sf::Color idleColor;
  sf::Color hoverColor;
  sf::Color activeColor;

  sf::Color outlineIdleColor;
  sf::Color outlineHoverColor;
  sf::Color outlineActiveColor;

  sf::Sound hoverSound;
  sf::Sound clickSound;
};

class TextField : public Widget {
public:
  TextField(float x, float y, float w, float h, short unsigned id,
            sf::Font *font, std::string text, unsigned charSize,
            sf::Color textColor, sf::Color shapeColor, sf::Color outlineColor);
  ~TextField() { delete this->font; }
  virtual void update(sf::Event event);
  std::string getText();
  void setText(std::string text);

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  sf::RectangleShape shape;
  sf::Font *font;
  sf::Text text;

  sf::Color textColor;

  sf::Color shapeColor;

  sf::Color outlineColor;
};
} // namespace GUI
}; // namespace Skeleton