#include <Components.hpp>
#include <GameState.hpp>
#include <Systems.hpp>

GameState::GameState(Skeleton::GameDataRef Data)
	: GraphicsSystem(Tanks), OthersSystem(Tanks), Data(Data) {}

void GameState::init() {
	this->Script.script_file("scripts/RedTank.lua");
	this->RedTank = this->Tanks.create<Tank>(this->Data, "scripts/RedTank.lua");
	// this->BlueTank =
		// this->Tanks.create<Tank>(this->Data, "scripts/BlueTank.lua");

	this->GraphicsSystem.add<GraphicSystem>(this->Data);
	this->OthersSystem.add<MovingSystem>();
	this->OthersSystem.add<LogicSystem>();
}

void GameState::handleInput() {
	sf::Event event;
	while (this->Data->Window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->Data->Window.close();
		}
	}
}

void GameState::update(float dt) {
	this->Data->Window.clear(sf::Color(125, 125, 125));
	// 	if (turn)
	this->GraphicsSystem.update(dt);
	this->OthersSystem.update(dt);
}

void GameState::draw() {
	ImGui::SFML::Update(this->Data->Window, this->Clock.restart());

	if (this->Data->DebugMode) {
		ImGui::Begin("Debug Red Tank.");
		std::stringstream Redss;

		sf::Vector2f RedPosition =
			this->RedTank.get<MovableGraphicComponent>().Sprite.getPosition();
		Redss << "(" << RedPosition.x << "," << RedPosition.y << ")";
		ImGui::LabelText(Redss.str().c_str(), "Position:");

		Redss.str("");
		sf::Vector2f RedOrigin =
			this->RedTank.get<MovableGraphicComponent>().Sprite.getOrigin();
		Redss << "(" << RedOrigin.x << "," << RedOrigin.y << ")";
		ImGui::LabelText(Redss.str().c_str(), "Origin:");

		Redss.str("");
		sf::Vector2f RedScale =
			this->RedTank.get<MovableGraphicComponent>().Sprite.getScale();
		Redss << "(" << RedScale.x << "," << RedScale.y << ")";
		ImGui::LabelText(Redss.str().c_str(), "Scale:");

		Redss.str("");
		Redss << this->RedTank.get<MovableGraphicComponent>()
						 .Sprite.getRotation() +
					 this->RedTank.get<MovableGraphicComponent>().SpriteRotation
			  << "°";
		ImGui::LabelText(Redss.str().c_str(), "Angle:");

		Redss.str("");
		Redss << this->RedTank.get<MovableGraphicComponent>().Speed;
		ImGui::LabelText(Redss.str().c_str(), "Speed:");
		ImGui::End();

		// ImGui::Begin("Debug Blue Tank.");
		// std::stringstream Bluess;

		// sf::Vector2f BluePosition =
		// 	this->BlueTank.get<MovableGraphicComponent>().Sprite.getPosition();
		// Bluess << "(" << BluePosition.x << "," << BluePosition.y << ")";
		// ImGui::LabelText(Bluess.str().c_str(), "Position:");

		// Bluess.str("");
		// sf::Vector2f BlueOrigin =
		// 	this->BlueTank.get<MovableGraphicComponent>().Sprite.getOrigin();
		// Bluess << "(" << BlueOrigin.x << "," << BlueOrigin.y << ")";
		// ImGui::LabelText(Bluess.str().c_str(), "Origin:");

		// Bluess.str("");
		// sf::Vector2f BlueScale =
		// 	this->BlueTank.get<MovableGraphicComponent>().Sprite.getScale();
		// Bluess << "(" << BlueScale.x << "," << BlueScale.y << ")";
		// ImGui::LabelText(Bluess.str().c_str(), "Scale:");

		// Bluess.str("");
		// Bluess
		// 	<< this->BlueTank.get<MovableGraphicComponent>()
		// 			   .Sprite.getRotation() +
		// 		   this->BlueTank.get<MovableGraphicComponent>().SpriteRotation
		// 	<< "°";
		// ImGui::LabelText(Bluess.str().c_str(), "Angle:");

		// Bluess.str("");
		// Bluess << this->BlueTank.get<MovableGraphicComponent>().Speed;
		// ImGui::LabelText(Bluess.str().c_str(), "Speed:");
		// ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::SFML::Render(this->Data->Window);
	this->Data->Window.display();
}
