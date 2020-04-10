#pragma once
#include <Components.hpp>
#include <ECS.hpp>
#include <Engine.hpp>

class drawGraphicSystem : public Skeleton::System {
public:
  Skeleton::gameDataRef data;
  drawGraphicSystem(Skeleton::gameDataRef data) : data(data) {}
  void update(float time) override {
    // Get the entity manager using entities() function
    for (auto entity : entities().with<GraphicComponent>()) {
      entity.get<GraphicComponent>().update(time);
      this->data->window.draw(entity.get<GraphicComponent>().sprite);
    }
  }
};