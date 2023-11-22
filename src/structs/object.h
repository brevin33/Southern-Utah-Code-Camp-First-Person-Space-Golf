#pragma once
#include "../defines.h"
#include <GLFW/glfw3.h>


struct VulkanObject
{
	void cleanup() {
		vkDestroyDescriptorPool(*device, descriptorPool, nullptr);
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroyBuffer(*device, uniformBuffers[i], nullptr);
			vkFreeMemory(*device, uniformBuffersMemory[i], nullptr);
		}
	}

	MeshID meshID;
	ShaderID shaderID;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;
	VkDevice* device;

};