#include <Tank.hpp>

Tank::Tank(Skeleton::GameDataRef Data, sol::table GC, std::string Path,
		   float Speed) {
	this->add<GraphicComponent>(Data, GC);
	this->add<LogicComponent>(Path);
	this->get<LogicComponent>().L.set_function("rotate", &Tank::rotate, *this);
	this->get<LogicComponent>().L.set_function("move", &Tank::move, *this);
	this->add<MovableComponent>(Speed);
}

Tank::~Tank() {}

void Tank::rotate(float Angle) {
	this->get<GraphicComponent>().Sprite.rotate(Angle);
}

void Tank::move() { this->get<MovableComponent>().Speed = 5; }