#include <Tank.hpp>

Tank::Tank(Skeleton::GameDataRef Data, sol::table GC, std::string Path) {
	this->add<MovableGraphicComponent>(Data, GC);
	this->add<LogicComponent>(Path);
	this->get<LogicComponent>().L.set_function("rotate", &Tank::rotate, *this);
	this->get<LogicComponent>().L.set_function("forward", &Tank::forward,
											   *this);
	this->get<LogicComponent>().L.set_function("backward", &Tank::backward,
											   *this);
	this->get<LogicComponent>().L.set_function("stop", &Tank::stop, *this);
}

Tank::~Tank() {}

void Tank::rotate(float Angle) {
	this->get<MovableGraphicComponent>().Sprite.rotate(Angle);
}

void Tank::forward() { this->get<MovableGraphicComponent>().Speed = 5; }
void Tank::backward() { this->get<MovableGraphicComponent>().Speed = -5; }
void Tank::stop() { this->get<MovableGraphicComponent>().Speed = 0; }