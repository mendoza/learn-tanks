#pragma once
#include <Engine.hpp>
#include <SFML/Graphics.hpp>
#include <sol.hpp>

class Component {
  public:
	virtual void update(float dt){};
	virtual void draw(){};
	virtual ~Component(){};
};

class GraphicComponent : public Component {
  public:
	sf::Sprite Sprite;
	sf::Vector2u ImageCount;
	sf::Vector2u CurrentImage;
	std::string Name;
	sf::IntRect UvRect;
	float SwitchTime;
	float TotalTime = 0.0f;
	bool Animated = false;
	int Row = 0;

	GraphicComponent(Skeleton::GameDataRef Data, sol::table GC) {
		this->Name = GC["spriteName"];
		Data->Assets.loadTexture(this->Name, GC["spriteFilepath"]);
		sf::Texture &text = Data->Assets.getTexture(this->Name);
		sf::Vector2f scale(GC["scale"]["width"], GC["scale"]["height"]);
		sf::Vector2f origin(GC["origin"]["x"], GC["origin"]["y"]);
		this->Sprite.setOrigin(origin);
		this->Sprite.setTexture(text);
		this->Sprite.setScale(scale);
	}

	void update(float dt) override {
		if (this->Animated) {
			this->TotalTime += dt;
			if (TotalTime >= SwitchTime) {
				TotalTime -= SwitchTime;
				CurrentImage.x++;
				if (CurrentImage.x >= ImageCount.x) {
					CurrentImage.x = 0;
				}
			}
			UvRect.left = CurrentImage.x * UvRect.width;
			UvRect.top = CurrentImage.y * UvRect.height;
			this->Sprite.setTextureRect(this->UvRect);
		}
	}
};