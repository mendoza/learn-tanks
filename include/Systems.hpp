#pragma once
#include <Components.hpp>
#include <Engine.hpp>

class GraphicSystem : public ecs::System {
  public:
	Skeleton::GameDataRef Data;
	GraphicSystem(Skeleton::GameDataRef Data) : Data(Data) {}
	void update(float time) override {
		// Get the entity manager using entities() function
		for (auto entity : entities().with<GraphicComponent>()) {
			entity.get<GraphicComponent>().update(time);
			this->Data->Window.draw(entity.get<GraphicComponent>().Sprite);
		}
	}
};

class LogicSystem : public ecs::System {
  public:
	LogicSystem() {}

	void update(float time) override {
		// Get the entity manager using entities() function
		for (auto entity : entities().with<LogicComponent>()) {
			entity.get<LogicComponent>().update(time);
		}
	}
};