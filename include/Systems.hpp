#pragma once
#include <Components.hpp>
#include <Engine.hpp>

class GraphicSystem : public ecs::System {
  public:
	Skeleton::GameDataRef Data;
	GraphicSystem(Skeleton::GameDataRef Data) : Data(Data) {}
	void update(float time) override {
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
		for (auto entity : entities().with<LogicComponent>()) {
			entity.get<LogicComponent>().update(time);
		}
	}
};

class MovableSystem : public ecs::System {
  public:
	MovableSystem() {}

	void update(float time) override {
		for (auto entity :
			 entities().with<MovableComponent, GraphicComponent>()) {
			entity.get<MovableComponent>().update(time);
			sf::Vector2f Direction;
			float angle = entity.get<GraphicComponent>().Sprite.getRotation();
			Direction.x = std::cos(angle);
			Direction.y = std::sin(angle);

			entity.get<GraphicComponent>().Position +=
				Direction * entity.get<MovableComponent>().Speed;
		}
	}
};