#pragma once
#include <Components.hpp>
#include <Engine.hpp>

class GraphicSystem : public ecs::System {
  public:
	Skeleton::GameDataRef Data;
	GraphicSystem(Skeleton::GameDataRef Data) : Data(Data) {}
	void update(float time) override {
		for (auto entity : entities().with<MovableGraphicComponent>()) {
			entity.get<MovableGraphicComponent>().update(time);
			this->Data->Window.draw(
				entity.get<MovableGraphicComponent>().Sprite);
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

class MovingSystem : public ecs::System {
  public:
	Skeleton::GameDataRef Data;
	MovingSystem() {}
	void update(float time) override {
		for (auto entity : entities().with<MovableGraphicComponent>()) {
			entity.get<MovableGraphicComponent>().update(time);

			sf::Vector2f Direction;
			float angle =
				entity.get<MovableGraphicComponent>().Sprite.getRotation() +
				entity.get<MovableGraphicComponent>().SpriteRotation;

			Direction.x = std::cos(angle * M_PI / 180);
			Direction.y = -std::sin(angle * M_PI / 180);

			entity.get<MovableGraphicComponent>().Sprite.move(
				Direction * entity.get<MovableGraphicComponent>().Speed);
		}
	}
};
