#include <AssetManager.hpp>

namespace Skeleton {
void AssetManager::loadTexture(std::string name, std::string filename) {
  sf::Texture tex;
  if (tex.loadFromFile(filename)) {
    this->textures[name] = tex;
  }
}

sf::Texture &AssetManager::getTexture(std::string name) {
  return this->textures.at(name);
}

void AssetManager::loadFont(std::string name, std::string filename) {
  sf::Font font;
  if (font.loadFromFile(filename)) {
    this->fonts[name] = font;
  }
}

sf::Font &AssetManager::getFont(std::string name) {
  return this->fonts.at(name);
}

void AssetManager::loadSound(std::string name, std::string filename) {
  sf::SoundBuffer soundbuffer;
  if (soundbuffer.loadFromFile(filename)) {
    this->soundBuffers[name] = soundbuffer;
  }
}

sf::SoundBuffer &AssetManager::getSound(std::string name) {
  return this->soundBuffers.at(name);
}

} // namespace Skeleton