#include <Game.hpp>
#include <SplashState.hpp>

namespace Skeleton {
Game::Game(int width, int height, std::string title, std::string iconFile,
           int limit) {
  sf::Image image;
  image.loadFromFile(iconFile);
  this->data->window.create(sf::VideoMode(width, height), title);
  this->data->window.setIcon(image.getSize().x, image.getSize().y,
                             image.getPixelsPtr());
  this->data->window.setFramerateLimit(limit);
  this->data->machine.addState(StateRef(new SplashState(this->data)));
  this->run();
}

void Game::run() {
  float frametime;
  float accumulator = 0.0f;
  while (this->data->window.isOpen()) {
    this->data->machine.processStateChanges();

    while (accumulator > dt) {
      accumulator -= dt;
      this->data->machine.getActiveState()->handleInput();
      this->data->machine.getActiveState()->update(dt);
    }

    frametime = this->_clock.restart().asSeconds();
    accumulator += frametime;
    // printf("FPS: %d\n", (int)(1.0f / frametime));
    this->data->machine.getActiveState()->draw();
  }
}
} // namespace Skeleton