#pragma once
#include "../defines.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

struct collider{
	EntityID ID;
	float radius;
	glm::vec3 pos;
};