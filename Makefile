# based on https://gist.github.com/maxtruxa/4b3929e118914ccef057f8a05c614b0f
# edited by Valentin Peltier

# output binary
OUT := bin/MyTinyFarm.out
# source directory
SRC_DIR := src
# shaders directory
SHADERS_DIR := shaders
# intermediate directory for generated object files and dependency files
OBJ_DIR := obj

# source files
SOURCE := $(shell find $(SRC_DIR) -name "*.cpp")
# object files, auto generated from source files
OBJS := $(patsubst src/%,$(OBJ_DIR)/%.o,$(basename $(SOURCE)))
# dependency files, auto generated from source files
DEPS := $(patsubst src/%,$(OBJ_DIR)/%.d,$(basename $(SOURCE)))
# vertex shader object files (spir-v format), auto-generated from shader source files
VERTEX_OBJS := $(patsubst %.vert, %.vert.spv, $(shell find ./shaders -type f -name "*.vert"))
# fragment shader object files (spir-v format), auto-generated from shader source files
FRAGMENT_OBJS := $(patsubst %.frag, %.frag.spv, $(shell find ./shaders -type f -name "*.frag"))

# C++ compiler
CXX := g++
# linker
LD := g++
# GLSL compiler
GLSLC := glslc
# C++ flags
CXXFLAGS := -g -Wall -Wextra -O0 -I./libs
# linker flags
LDFLAGS := -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF $(OBJ_DIR)/$*.d

# compilers (at least gcc and clang) don't create the subdirectories automatically
$(shell mkdir -p $(dir $(OUT)) >/dev/null)
$(shell mkdir -p $(dir $(OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(DEPS)) >/dev/null)

##################
##################
##################

all: $(VERTEX_OBJS) $(FRAGMENT_OBJS) $(OUT)

$(OUT): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

%.spv: %
	$(GLSLC) $< -o $@

##################
##################
##################

.PHONY: test
test: $(VERTEX_OBJS) $(FRAGMENT_OBJS) $(OUT)
	./$(OUT)

.PHONY: clean
clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) $(SHADERS_DIR)/*.spv
	$(RM) $(OUT)

.PRECIOUS: $(OBJ_DIR)/%.d
$(OBJ_DIR)/%.d: ;

-include $(DEPS)