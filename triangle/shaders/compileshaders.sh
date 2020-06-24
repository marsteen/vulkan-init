#!/bin/sh
VK_BIN=/c/VulkanSDK/1.2.141.2/Bin

$VK_BIN/glslc shader.vert -o vert.spv
$VK_BIN/glslc shader.frag -o frag.spv