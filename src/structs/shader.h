#pragma once
#include "../defines.h"
#include <GLFW/glfw3.h>

struct VulkanShader {

	void cleanup() {
		vkDestroyPipeline(*device, graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(*device, pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(*device, descriptorSetLayout, nullptr);

	}

	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	VkDescriptorSetLayout descriptorSetLayout;
	VkDevice* device;
};