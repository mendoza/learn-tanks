#pragma once
#include <Components.hpp>
#include <Engine.hpp>

class drawGraphicSystem : public ecs::System {
  public:
	Skeleton::GameDataRef Data;
	drawGraphicSystem(Skeleton::GameDataRef data) : Data(data) {}
	void update(float time) override {
		// Get the entity manager using entities() function
		for (auto entity : entities().with<GraphicComponent>()) {
			entity.get<GraphicComponent>().update(time);
			this->Data->Window.draw(entity.get<GraphicComponent>().Sprite);
		}
	}
};