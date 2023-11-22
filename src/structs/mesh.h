#pragma once
#include "../defines.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
#include "vertex.h"
struct VulkanMesh
{

	void cleanup() {
		vkDestroyBuffer(*device, indexBuffer, nullptr);
		vkFreeMemory(*device, indexBufferMemory, nullptr);

		vkDestroyBuffer(*device, vertexBuffer, nullptr);
		vkFreeMemory(*device, vertexBufferMemory, nullptr);
	}

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	VkDevice* device;
	uint32_t indicesSize;
};

struct Mesh 
{
	std::vector<Vertex> vertices;
	std::vector< uint32_t> indices;

	void makeCircle(int subdivisions);
};