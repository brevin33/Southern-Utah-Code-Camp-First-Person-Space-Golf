#pragma once
#include "vulkanEngine.h"
#include "gameEngineGame.h"
#include "components/player.h"
#include "components/collider.h"
class FirstPersonSpaceGolf: public Game
{
public:
	player player;
public:
	void run();
	void update();
	glm::mat4x4 getView();
private:
	VulkanEngine engine;
	std::vector<collider> colliders;
private:
	void setup();
	void createPlanet(glm::vec3 pos, glm::vec3 color);
};

