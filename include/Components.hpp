#pragma once
#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <sol.hpp>

namespace Skeleton {
class Component {
public:
  virtual void update(float dt){};
  virtual void draw(){};
  virtual ~Component(){};
};

class GraphicComponent : public Component {
public:
  sf::Sprite sprite;
  sf::Vector2u imageCount;
  sf::Vector2u currentImage;
  std::string name;
  sf::IntRect uvRect;
  float switchTime;
  float totalTime = 0.0f;
  bool animated = false;
  int row = 0;

  GraphicComponent(gameDataRef data, sol::table gc) {
    this->name = gc["spriteName"];
    data->assets.loadTexture(this->name, gc["spriteFilepath"]);
    sf::Texture &text = data->assets.getTexture(this->name);
    sf::Vector2f scale(gc["scale"]["width"], gc["scale"]["height"]);
    this->sprite.setTexture(text);
    this->sprite.setScale(scale);
  }

  void update(float dt) override {
    if (this->animated) {
      this->totalTime += dt;
      if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= imageCount.x) {
          currentImage.x = 0;
        }
      }
      uvRect.left = currentImage.x * uvRect.width;
      uvRect.top = currentImage.y * uvRect.height;
      this->sprite.setTextureRect(this->uvRect);
    }
  }
};

} // namespace Skeleton