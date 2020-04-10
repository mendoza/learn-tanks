#pragma once
#include <AssetManager.hpp>
#include <ECS.hpp>
#include <InputManager.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <StateMachine.hpp>
#include <memory>
#include <string>

namespace Skeleton {
using namespace ecs;
struct gameData {
  StateMachine machine;
  sf::RenderWindow window;
  AssetManager assets;
  InputManager input;
  sf::Clock _clock;
};

typedef std::shared_ptr<gameData> gameDataRef;
class Engine {
public:
  Engine(int width, int height, std::string title, std::string, int limit = 60,
         bool vSync = false);

private:
  sf::Clock _clock;
  const float dt = 1.0f / 6.0f;
  gameDataRef data = std::make_shared<gameData>();
  void run();
};
}; // namespace Skeleton