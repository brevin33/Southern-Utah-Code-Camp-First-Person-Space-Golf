#pragma once

#include "../defines.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

struct Transform {
	EntityID ID;
	glm::mat4x4 model;
	glm::vec3 color;
};

