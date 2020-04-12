#include <Components.hpp>

class Tank : public ecs::EntityAlias<GraphicComponent, LogicComponent,
									 MovableComponent> {
  public:
	Tank() {}
	Tank(Skeleton::GameDataRef Data, sol::table GC, std::string Path,
		 float Speed);
	~Tank();
	void rotate(float Angle);
	void move();

  private:
};