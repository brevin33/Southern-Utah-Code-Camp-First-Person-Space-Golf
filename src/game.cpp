#include "game.h"
#include <chrono>
#include <iostream>
FirstPersonSpaceGolf* thisGame;
bool firstMouse = true;
float lastX;
float lastY;
auto lastTime = std::chrono::high_resolution_clock::now();
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    thisGame->player.handelMouseMovement(xoffset, yoffset);
}

void FirstPersonSpaceGolf::run()
{
	setup();
	engine.run();
}

void FirstPersonSpaceGolf::update()
{
    if (glfwGetKey(engine.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(engine.window, true);

    engine.playerPos = player.pos;
    auto currentTime = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
    lastTime = currentTime;
    player.update(dt*16, glm::vec3(0, 0, 0), glfwGetMouseButton(engine.window,0), colliders);
}

glm::mat4x4 FirstPersonSpaceGolf::getView() {
    return player.GetViewMatrix();
}

void FirstPersonSpaceGolf::createPlanet(glm::vec3 pos, glm::vec3 color) {
    EntityID e = engine.createEnity();
    Mesh circle;
    circle.makeCircle(4);
    engine.addMeshRenderer(e, &circle, "src/shaders/planetVert.spv", "src/shaders/planetFrag.spv");
    engine.moveEntity(e,pos);
    engine.changeColor(e,color);
    collider c;
    c.ID = e;
    c.pos = pos;
    c.radius = 0.5;
    colliders.push_back(c);
}

void FirstPersonSpaceGolf::setup()
{
	thisGame = this;
	engine.setup(this);
    createPlanet(glm::vec3(0,0,0),glm::vec3(0.3f,0.8f,0.3f));
    createPlanet(glm::vec3(-8, -6, -10),glm::vec3(0.7f,0.6f,0.3f));
    createPlanet(glm::vec3(6, -9, -6), glm::vec3(0.7f, 0.5f, 0.7f));
    createPlanet(glm::vec3(-7, 7, 5), glm::vec3(0.2f, 0.2f, 0.9f));
    createPlanet(glm::vec3(5, 8, 8), glm::vec3(0.2f, 0.6f, 0.85f));

	glfwSetCursorPosCallback(engine.window, mouse_callback);
    glfwSetInputMode(engine.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
