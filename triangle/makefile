#**********************************************************************
#
# Vulkan testproject makefile
#
#**********************************************************************

ifeq ($(OS),Windows_NT)
  OS_SYS   = Windows
else
  OS_SYS := $(shell uname -s)
endif

#**********************************************************************
#
# Windows settings
#
#**********************************************************************

ifeq ($(OS_SYS),Windows)

TARGET_OS   = windows
VULKAN_SDK  = /c/VulkanSDK/1.2.141.2
GLSLC       = $(VULKAN_SDK)/bin/glslc
CCFLAGS     = -O2 -std=gnu++17 -I./source -I$(VULKAN_SDK)/include
LDFLAGS     = -L$(VULKAN_SDK)/Lib -lvulkan-1 -lglfw3

endif

#**********************************************************************
#
# Linux settings
#
#**********************************************************************

ifeq ($(OS_SYS),Linux)

TARGET_OS   = linux
GLSLC       = glslc
CCFLAGS     = -O2 -std=gnu++17
LDFLAGS     = -lvulkan -lglfw

endif

#**********************************************************************
#
# Mac OS settings
#
#**********************************************************************

ifeq ($(OS_SYS),Darwin)

TARGET_OS   = macos
GLSLC       = glslc
FRAMEWORKS  = -framework IOKit \
             -framework Foundation \
             -framework Cocoa -framework CoreAudio -framework Carbon -framework AudioUnit
CCFLAGS     = -O2 -std=gnu++17
LDFLAGS = $(FRAMEWORKS) -L$(GLFW_PATH)/lib-macos -lvulkan -lglfw3

endif

#**********************************************************************
#
#**********************************************************************

C++ = g++

#
#
#
.SUFFIXES : .cpp .o .vert .frag .spv
#
#
#
CPPFILES = source/main.cpp \
           source/CVulkanApp.cpp

VERT_SHADERS = shaders/shader-vert.vert
FRAG_SHADERS = shaders/shader-frag.frag

#
TARGET   = bin/$(TARGET_OS)/vulkan-triangle
#
default : $(TARGET)
#
clean:
	rm -f $(OBJECTS)
#
#
.cpp.o:
	$(C++) -c $(CCFLAGS) -o$@ $<

.c.o:
	gcc -c $(CCFLAGS) -o$@ $<

.vert.spv:
	$(GLSLC) -o$@ $<

.frag.spv:
	$(GLSLC) -o$@ $<
#
OBJECTS1 = $(CPPFILES:.cpp=.o)
OBJECTS2 = $(CFILES:.c=.o)
VERT_OBJECTS = $(VERT_SHADERS:.vert=.spv)
FRAG_OBJECTS = $(FRAG_SHADERS:.frag=.spv)
OBJECTS = $(OBJECTS1) $(OBJECTS2) $(VERT_OBJECTS) $(FRAG_OBJECTS)
#
#
$(TARGET) : $(OBJECTS)
	$(C++) -s -o $(TARGET) $(OBJECTS1) $(OBJECTS2) $(LDFLAGS)
	cp ./shaders/*.spv ./bin/$(TARGET_OS)/shaders

