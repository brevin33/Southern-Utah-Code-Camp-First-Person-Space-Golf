#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
class Game {
public:
	virtual void update() = 0;
	virtual glm::mat4x4 getView() = 0;
};