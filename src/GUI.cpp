#include <GUI.hpp>
#include <cmath>

namespace Skeleton {
namespace GUI {
const float p2pX(float Perc, sf::RenderWindow *Window) {
	return std::ceil(static_cast<float>(Window->getSize().x) * (Perc / 100.f));
}

const float p2pY(float Perc, sf::RenderWindow *Window) {
	return std::ceil(static_cast<float>(Window->getSize().y) * (Perc / 100.f));
}

const unsigned calcCharSize(sf::RenderWindow *Window, const unsigned Modifier) {
	return static_cast<unsigned>((Window->getSize().x + Window->getSize().y) /
								 Modifier);
}

Button::Button(float X, float Y, float W, float H, short unsigned Id,
			   sf::Font *Font, std::string Text, unsigned CharSize,
			   sf::Color TextIdleColor, sf::Color TextHoverColor,
			   sf::Color TextActiveColor, sf::Color IdleColor,
			   sf::Color HoverColor, sf::Color ActiveColor,
			   sf::SoundBuffer *HoverSound, sf::SoundBuffer *ClickSound,
			   sf::Color OutlineIdleColor, sf::Color OutlineHoverColor,
			   sf::Color OutlineActiveColor)
	: Widget(Id) {
	this->ButtonState = BTN_IDLE;

	this->Shape.setPosition(sf::Vector2f(X, Y));
	this->Shape.setSize(sf::Vector2f(W, H));
	this->Shape.setFillColor(IdleColor);
	this->Shape.setOutlineThickness(1.f);
	this->Shape.setOutlineColor(OutlineIdleColor);

	this->Font = Font;
	this->Text.setFont(*this->Font);
	this->Text.setString(Text);
	this->Text.setFillColor(TextIdleColor);
	this->Text.setCharacterSize(CharSize);
	this->Text.setPosition(this->Shape.getPosition().x +
							   (this->Shape.getGlobalBounds().width / 2.f) -
							   this->Text.getGlobalBounds().width / 2.f,
						   this->Shape.getPosition().y);

	this->TextIdleColor = TextIdleColor;
	this->TextHoverColor = TextHoverColor;
	this->TextActiveColor = TextActiveColor;

	this->IdleColor = IdleColor;
	this->HoverColor = HoverColor;
	this->ActiveColor = ActiveColor;

	this->OutlineIdleColor = OutlineIdleColor;
	this->OutlineHoverColor = OutlineHoverColor;
	this->OutlineActiveColor = OutlineActiveColor;

	this->ClickSound = sf::Sound(*ClickSound);
	this->HoverSound = sf::Sound(*HoverSound);

	this->ClickSound.setLoop(false);
	this->HoverSound.setLoop(false);

	this->HasPlayed = false;
}

void Button::draw(sf::RenderTarget &Target, sf::RenderStates States) const {
	Target.draw(this->Shape, States);
	Target.draw(this->Text, States);
}

void Button::update(const sf::Vector2i MousePos) {
	this->ButtonState = BTN_IDLE;
	sf::IntRect tempRect(this->Shape.getPosition().x,
						 this->Shape.getPosition().y,
						 this->Shape.getGlobalBounds().width,
						 this->Shape.getGlobalBounds().height);
	if (tempRect.contains(MousePos)) {
		this->ButtonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->ButtonState = BTN_ACTIVE;
		}
	}

	switch (this->ButtonState) {
	case BTN_IDLE:
		this->HasPlayed = false;
		this->Shape.setFillColor(this->IdleColor);
		this->Text.setFillColor(this->TextIdleColor);
		this->Shape.setOutlineColor(this->OutlineIdleColor);
		break;

	case BTN_HOVER:
		if (this->HoverSound.Playing != this->HoverSound.getStatus() &&
			!HasPlayed) {
			this->HoverSound.play();
			this->HasPlayed = true;
		}
		this->Shape.setFillColor(this->HoverColor);
		this->Text.setFillColor(this->TextHoverColor);
		this->Shape.setOutlineColor(this->OutlineHoverColor);
		break;

	case BTN_ACTIVE:
		if (this->ClickSound.Playing != this->ClickSound.getStatus())
			this->ClickSound.play();
		this->Shape.setFillColor(this->ActiveColor);
		this->Text.setFillColor(this->TextActiveColor);
		this->Shape.setOutlineColor(this->OutlineActiveColor);
		break;

	default:
		this->Shape.setFillColor(sf::Color::Red);
		this->Text.setFillColor(sf::Color::Blue);
		this->Shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

const bool Button::isPressed() const { return this->ButtonState == BTN_ACTIVE; }

TextField::TextField(float X, float Y, float W, float H, short unsigned Id,
					 sf::Font *Font, std::string Text, unsigned CharSize,
					 sf::Color TextColor, sf::Color ShapeColor,
					 sf::Color OutlineColor)
	: Widget(Id) {
	this->Shape.setPosition(sf::Vector2f(X, Y));
	this->Shape.setSize(sf::Vector2f(W, H));
	this->Shape.setFillColor(ShapeColor);
	this->Shape.setOutlineThickness(1.f);
	this->Shape.setOutlineColor(OutlineColor);

	this->Font = Font;
	this->Text.setFont(*this->Font);
	this->Text.setString(Text);
	this->Text.setFillColor(TextColor);
	this->Text.setCharacterSize(CharSize);
	this->Text.setPosition(this->Shape.getPosition().x -
							   this->Text.getGlobalBounds().width / 2.f,
						   this->Shape.getPosition().y);

	this->TextColor = TextColor;
	this->ShapeColor = ShapeColor;
	this->OutlineColor = OutlineColor;
}

void TextField::draw(sf::RenderTarget &Target, sf::RenderStates States) const {
	Target.draw(this->Shape, States);
	Target.draw(this->Text, States);
}

void TextField::update(sf::Event Event) {
	if (sf::Event::TextEntered == Event.type &&
		(this->Text.getGlobalBounds().width <=
			 this->Shape.getGlobalBounds().width ||
		 Event.text.unicode == '\b')) {
		std::string str = this->Text.getString();
		if (Event.text.unicode == '\b')
			str = str.substr(0, str.size() - 1);
		else if (Event.text.unicode < 128)
			str += static_cast<char>(Event.text.unicode);
		this->setText(str);
	}
}
std::string TextField::getText() { return this->Text.getString(); }

void TextField::setText(std::string Text) { this->Text.setString(Text); }
}; // namespace GUI
}; // namespace Skeleton
