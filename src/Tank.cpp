#include <Tank.hpp>

Tank::Tank(Skeleton::GameDataRef Data, std::string Path) {
	sol::state L;
	L.script_file(Path);
	sol::table Player = L["Tank"];

	this->add<MovableGraphicComponent>(Data, Player["movableGraphicComponent"]);
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
	this->stop();
	this->get<MovableGraphicComponent>().Sprite.rotate(Angle);
}

void Tank::forward() {
	float speed = this->get<LogicComponent>()
					  .L["Tank"]["movableGraphicComponent"]["speed"];
	this->get<MovableGraphicComponent>().Speed = speed;
}

void Tank::backward() {
	float speed = this->get<LogicComponent>()
					  .L["Tank"]["movableGraphicComponent"]["speed"];
	this->get<MovableGraphicComponent>().Speed = -speed;
}
void Tank::stop() { this->get<MovableGraphicComponent>().Speed = 0; }