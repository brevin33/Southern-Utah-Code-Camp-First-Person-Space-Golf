#pragma once
#include <inttypes.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#define GLFW_INCLUDE_VULKAN
#define STB_IMAGE_IMPLEMENTATION

constexpr int MAX_FRAMES_IN_FLIGHT = 2;
#define MAXSHADERS 10
#define MAXSMESHES 10
#define MAXOBJECTS 10
#define WIDTH 1920
#define HEIGHT 1080


#define EntityID uint16_t
#define ShaderID uint16_t
#define MeshID uint16_t
#define ObjectID uint16_t
#define ComponentID uint16_t


#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif