#include <Tank.hpp>

Tank::Tank(Skeleton::GameDataRef Data, std::string Path, sol::table GC) {
	this->add<GraphicComponent>(Data, GC);
	this->add<LogicComponent>(Path);
	this->get<LogicComponent>().L.set_function("rotate", &Tank::rotate, *this);
}

Tank::~Tank() {}

const void Tank::rotate(float Angle) {
	this->get<GraphicComponent>().Sprite.rotate(Angle);
}
