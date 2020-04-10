#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
namespace Skeleton {
namespace GUI {
enum ButtonStates { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };
const float p2pX(float Perc, sf::RenderWindow *Window);
const float p2pY(float Perc, sf::RenderWindow *Window);
const unsigned calcCharSize(sf::RenderWindow *Window,
							const unsigned Modifier = 60);

class Widget : public sf::Drawable {
  public:
	Widget(short unsigned Id) { this->Id = Id; }
	~Widget() {}

  private:
	short unsigned Id;
	virtual void draw(sf::RenderTarget &Target, sf::RenderStates States) const {
	}
	virtual void update() {}
};

class Button : public Widget {
	short unsigned ButtonState;

  public:
	Button(float X, float Y, float W, float H, short unsigned Id,
		   sf::Font *Font, std::string Text, unsigned CharSize,
		   sf::Color TextIdle, sf::Color TextHover, sf::Color TextActive,
		   sf::Color Idle, sf::Color Hover, sf::Color Active,
		   sf::SoundBuffer *HoverSound, sf::SoundBuffer *ClickSound,
		   sf::Color OutlineIdle = sf::Color::Transparent,
		   sf::Color OutlineHover = sf::Color::Transparent,
		   sf::Color OutlineActive = sf::Color::Transparent);
	~Button() { delete this->Font; }
	virtual void update(const sf::Vector2i MousePos);
	const bool isPressed() const;

  private:
	virtual void draw(sf::RenderTarget &Target, sf::RenderStates States) const;

	bool HasPlayed;

	sf::RectangleShape Shape;
	sf::Font *Font;
	sf::Text Text;

	sf::Color TextIdleColor;
	sf::Color TextHoverColor;
	sf::Color TextActiveColor;

	sf::Color IdleColor;
	sf::Color HoverColor;
	sf::Color ActiveColor;

	sf::Color OutlineIdleColor;
	sf::Color OutlineHoverColor;
	sf::Color OutlineActiveColor;

	sf::Sound HoverSound;
	sf::Sound ClickSound;
};

class TextField : public Widget {
  public:
	TextField(float X, float Y, float W, float H, short unsigned Id,
			  sf::Font *Font, std::string Text, unsigned CharSize,
			  sf::Color TextColor, sf::Color ShapeColor,
			  sf::Color OutlineColor);
	~TextField() { delete this->Font; }
	virtual void update(sf::Event Event);
	std::string getText();
	void setText(std::string Text);

  private:
	virtual void draw(sf::RenderTarget &Target, sf::RenderStates States) const;
	sf::RectangleShape Shape;
	sf::Font *Font;
	sf::Text Text;

	sf::Color TextColor;

	sf::Color ShapeColor;

	sf::Color OutlineColor;
};
} // namespace GUI
}; // namespace Skeleton