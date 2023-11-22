#pragma once
#include "../defines.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
#include "collider.h"
#include <vector>



class player
{
public:
	glm::mat4x4 view;
	glm::mat4x4 projection;
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float Yaw;
	float Pitch;
	float MouseSensitivity;
	float Zoom;
	float radius;

	float charge = 0;
	float fule = 1;
	bool landed = true;
	bool mouseDown = false;


public:
	player();

	void update(float dt, glm::vec3 input, bool mouseDown, std::vector<collider>& colliders);
	void handelMouseMovement(float xoffset, float yoffset);
	void handelMouseClick();
	void handelKeyPress(glm::vec3 input);
	void handelMouseUp();
	void handelMouseStay(float dt);
	glm::mat4 GetViewMatrix();



private:


private:

	void updatePos(std::vector<collider>& colliders, float dt);
	void updateCameraVectors();
};

