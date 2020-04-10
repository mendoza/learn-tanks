#include <Engine.hpp>
#include <sol.hpp>
#include <string>
#include <vector>

int main() {
  sol::state script;
  script.script_file("scripts/MetaData.lua");
  sol::table meta = script["MetaData"];
  std::string title = meta["title"];
  std::string icon = meta["icon"];
  int width = meta["width"];
  int height = meta["height"];
  int limit = meta["fpsLimit"];
  bool vSync = meta["vSync"];
  Skeleton::Engine(width, height, title, icon, limit, vSync);
  return 0;
}