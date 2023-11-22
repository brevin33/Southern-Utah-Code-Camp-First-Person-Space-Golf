#include "player.h"
#include "collider.h"
player::player()
{
    pos = glm::vec3(2,2,2);
    front = glm::vec3(0,0,-1);
    up = glm::vec3(0,1,0);
    worldUp = glm::vec3(0,1,0);
    velocity = glm::vec3(0,0,0);
    acceleration = glm::vec3(0,0,0);
    Yaw = -90.0f;
    Pitch = 0.0f;
    MouseSensitivity = 0.1f;
    Zoom = 45.0f;
    radius = 1.0f;

    updateCameraVectors();

}
void player::update(float dt, glm::vec3 input, bool mouseDown, std::vector<collider>& colliders)
{
    if (mouseDown && !this->mouseDown) {
        handelMouseClick();
    }
    else if (!mouseDown && this->mouseDown) {
        handelMouseUp();
    }
    else if(mouseDown && this->mouseDown) {
        handelMouseStay(dt);
    }
    this->mouseDown = mouseDown;
	handelKeyPress(input);
	updatePos(colliders,dt);
}

void player::handelMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void player::handelMouseClick()
{
}

void player::handelKeyPress(glm::vec3 input)
{
    if (landed || (input.x == 0 && input.y == 0 && input.z == 0)) return;
    return;

}

void player::handelMouseUp()
{
    acceleration += front * (1 * 0.004f);
}

void player::handelMouseStay(float dt)
{
    //charge = 1;
}

glm::mat4 player::GetViewMatrix()
{
    return glm::lookAt(pos, pos + front, up);
}

void player::updatePos(std::vector<collider>& colliders, float dt)
{
    acceleration = acceleration * (1.0f - 0.3f * dt);
    glm::vec3 gravities = glm::vec3(0, 0, 0);
    for (size_t i = 0; i < colliders.size(); i++)
    {
        collider c = colliders[i];
        gravities += glm::normalize(c.pos - pos) * 0.000011f * dt;
        gravities += glm::normalize(c.pos - pos) * 0.00033f * dt * (1/ glm::distance(c.pos, pos));
    }
    acceleration += gravities;
    if (gravities != glm::vec3(0, 0, 0)){
        //worldUp = glm::normalize(gravities);
    }
    velocity += acceleration * dt;
    glm::vec3 newPos = pos + velocity;
    for (size_t i = 0; i < colliders.size(); i++)
    {
        collider c = colliders[i];
        float dist = glm::distance(c.pos, newPos);
        if (dist < c.radius + radius) {
            velocity = glm::vec3(0, 0, 0);
            acceleration = glm::vec3(0, 0, 0);
            newPos = pos;
        }
    }
    pos = newPos;
}

void player::updateCameraVectors()
{
    glm::vec3 Front;
    Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front.y = sin(glm::radians(Pitch));
    Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front = glm::normalize(Front);
    //right = glm::normalize(glm::cross(Front, worldUp));
    //up = glm::normalize(glm::cross(right, front));
}
