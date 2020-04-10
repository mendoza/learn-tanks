#pragma once
#include <AssetManager.hpp>
#include <InputManager.hpp>
#include <OpenECS.hpp>
#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <StateMachine.hpp>
#include <map>
#include <memory>
#include <string>

namespace Skeleton {
struct GameData {
	StateMachine Machine;
	sf::RenderWindow Window;
	AssetManager Assets;
	InputManager Input;
	sf::Clock _clock;
};

typedef std::shared_ptr<GameData> GameDataRef;
class Engine {
  public:
	Engine(int Width, int Height, std::string Title, std::string IconFile,
		   int Limit = 60, bool VSync = false);

  private:
	sf::Clock Clock;
	const float dt = 1.0f / 6.0f;
	GameDataRef Data = std::make_shared<GameData>();
	void run();
};
}; // namespace Skeleton