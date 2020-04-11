#include <Components.hpp>

class Tank : public ecs::EntityAlias<GraphicComponent, LogicComponent> {
  public:
	Tank() {}
	Tank(Skeleton::GameDataRef Data, std::string Path, sol::table GC);
	~Tank();
	const void rotate(float Angle);

  private:
};