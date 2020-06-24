#!/bin/sh
wget -qO - http://packages.lunarg.com/lunarg-signing-key-pub.asc | apt-key add -
wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.2.141-bionic.list http://packages.lunarg.com/vulkan/1.2.141/lunarg-vulkan-1.2.141-bionic.list
apt update
apt install vulkan-sdk
