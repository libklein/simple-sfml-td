# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/patrick/Code/rougelike-dev

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/patrick/Code/rougelike-dev/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/rougelike_dev.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rougelike_dev.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rougelike_dev.dir/flags.make

CMakeFiles/rougelike_dev.dir/src/main.cpp.o: CMakeFiles/rougelike_dev.dir/flags.make
CMakeFiles/rougelike_dev.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/Code/rougelike-dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rougelike_dev.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rougelike_dev.dir/src/main.cpp.o -c /home/patrick/Code/rougelike-dev/src/main.cpp

CMakeFiles/rougelike_dev.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rougelike_dev.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/Code/rougelike-dev/src/main.cpp > CMakeFiles/rougelike_dev.dir/src/main.cpp.i

CMakeFiles/rougelike_dev.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rougelike_dev.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/Code/rougelike-dev/src/main.cpp -o CMakeFiles/rougelike_dev.dir/src/main.cpp.s

CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.o: CMakeFiles/rougelike_dev.dir/flags.make
CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.o: ../src/TextureAtlas.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/Code/rougelike-dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.o -c /home/patrick/Code/rougelike-dev/src/TextureAtlas.cpp

CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/Code/rougelike-dev/src/TextureAtlas.cpp > CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.i

CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/Code/rougelike-dev/src/TextureAtlas.cpp -o CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.s

CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.o: CMakeFiles/rougelike_dev.dir/flags.make
CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.o: ../src/world/Map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/Code/rougelike-dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.o -c /home/patrick/Code/rougelike-dev/src/world/Map.cpp

CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/Code/rougelike-dev/src/world/Map.cpp > CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.i

CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/Code/rougelike-dev/src/world/Map.cpp -o CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.s

CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.o: CMakeFiles/rougelike_dev.dir/flags.make
CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.o: ../src/SpriteAtlas.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/Code/rougelike-dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.o -c /home/patrick/Code/rougelike-dev/src/SpriteAtlas.cpp

CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/Code/rougelike-dev/src/SpriteAtlas.cpp > CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.i

CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/Code/rougelike-dev/src/SpriteAtlas.cpp -o CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.s

CMakeFiles/rougelike_dev.dir/src/world/World.cpp.o: CMakeFiles/rougelike_dev.dir/flags.make
CMakeFiles/rougelike_dev.dir/src/world/World.cpp.o: ../src/world/World.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/Code/rougelike-dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/rougelike_dev.dir/src/world/World.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rougelike_dev.dir/src/world/World.cpp.o -c /home/patrick/Code/rougelike-dev/src/world/World.cpp

CMakeFiles/rougelike_dev.dir/src/world/World.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rougelike_dev.dir/src/world/World.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/Code/rougelike-dev/src/world/World.cpp > CMakeFiles/rougelike_dev.dir/src/world/World.cpp.i

CMakeFiles/rougelike_dev.dir/src/world/World.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rougelike_dev.dir/src/world/World.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/Code/rougelike-dev/src/world/World.cpp -o CMakeFiles/rougelike_dev.dir/src/world/World.cpp.s

CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.o: CMakeFiles/rougelike_dev.dir/flags.make
CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.o: ../src/objects/Sprite.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/Code/rougelike-dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.o -c /home/patrick/Code/rougelike-dev/src/objects/Sprite.cpp

CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/Code/rougelike-dev/src/objects/Sprite.cpp > CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.i

CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/Code/rougelike-dev/src/objects/Sprite.cpp -o CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.s

CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.o: CMakeFiles/rougelike_dev.dir/flags.make
CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.o: ../src/objects/Tile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/patrick/Code/rougelike-dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.o -c /home/patrick/Code/rougelike-dev/src/objects/Tile.cpp

CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/patrick/Code/rougelike-dev/src/objects/Tile.cpp > CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.i

CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/patrick/Code/rougelike-dev/src/objects/Tile.cpp -o CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.s

# Object files for target rougelike_dev
rougelike_dev_OBJECTS = \
"CMakeFiles/rougelike_dev.dir/src/main.cpp.o" \
"CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.o" \
"CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.o" \
"CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.o" \
"CMakeFiles/rougelike_dev.dir/src/world/World.cpp.o" \
"CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.o" \
"CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.o"

# External object files for target rougelike_dev
rougelike_dev_EXTERNAL_OBJECTS =

rougelike_dev: CMakeFiles/rougelike_dev.dir/src/main.cpp.o
rougelike_dev: CMakeFiles/rougelike_dev.dir/src/TextureAtlas.cpp.o
rougelike_dev: CMakeFiles/rougelike_dev.dir/src/world/Map.cpp.o
rougelike_dev: CMakeFiles/rougelike_dev.dir/src/SpriteAtlas.cpp.o
rougelike_dev: CMakeFiles/rougelike_dev.dir/src/world/World.cpp.o
rougelike_dev: CMakeFiles/rougelike_dev.dir/src/objects/Sprite.cpp.o
rougelike_dev: CMakeFiles/rougelike_dev.dir/src/objects/Tile.cpp.o
rougelike_dev: CMakeFiles/rougelike_dev.dir/build.make
rougelike_dev: CMakeFiles/rougelike_dev.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/patrick/Code/rougelike-dev/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable rougelike_dev"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rougelike_dev.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rougelike_dev.dir/build: rougelike_dev

.PHONY : CMakeFiles/rougelike_dev.dir/build

CMakeFiles/rougelike_dev.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rougelike_dev.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rougelike_dev.dir/clean

CMakeFiles/rougelike_dev.dir/depend:
	cd /home/patrick/Code/rougelike-dev/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/patrick/Code/rougelike-dev /home/patrick/Code/rougelike-dev /home/patrick/Code/rougelike-dev/cmake-build-debug /home/patrick/Code/rougelike-dev/cmake-build-debug /home/patrick/Code/rougelike-dev/cmake-build-debug/CMakeFiles/rougelike_dev.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rougelike_dev.dir/depend

