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
	sf::Vector2f Position;
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
		this->Sprite.setTexture(text);

		if (GC["origin"] != sol::nil) {
			sf::Vector2f origin(GC["origin"]["x"], GC["origin"]["y"]);
			this->Sprite.setOrigin(origin);
		}

		if (GC["scale"] != sol::nil) {
			sf::Vector2f scale(GC["scale"]["width"], GC["scale"]["height"]);
			this->Sprite.setScale(scale);
		}
		if (GC["position"] != sol::nil) {
			this->Position =
				sf::Vector2f(GC["position"]["x"], GC["position"]["y"]);
			this->Sprite.setPosition(Position);
		}
		// Maybe add it later...
		// if (GC["rotation"] != sol::nil) {
		// 	sf::Vector2f vector(GC["rotation"]["x"], GC["rotation"]["y"]);
		// 	float angle = std::atan(vector.y / vector.x) * 180 / M_PI;
		// 	this->Sprite.setRotation(angle);
		// }
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
		this->Sprite.setPosition(Position);
	}
};

class LogicComponent : public Component {
  public:
	sol::state L;
	sol::function ScriptUpdate;
	LogicComponent(std::string Path) {
		L.script_file(Path);
		L.open_libraries();
		this->ScriptUpdate = L["Tank"]["logicalComponent"]["update"];
	}
	void update(float dt) override { this->ScriptUpdate(); }

	void draw() override {}
};

class MovableComponent : public Component {
  public:
	float Speed;
	MovableComponent(float Speed) { this->Speed = Speed; }

	void update(float dt) override {}

	void draw() override {}
};