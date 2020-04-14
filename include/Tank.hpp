#include <Components.hpp>

class Tank : public ecs::EntityAlias<MovableGraphicComponent, LogicComponent> {
  public:
	Tank() {}
	Tank(Skeleton::GameDataRef Data, std::string Path);
	~Tank();
	void rotate(float Angle);
	void forward();
	void backward();
	void stop();

  private:
};