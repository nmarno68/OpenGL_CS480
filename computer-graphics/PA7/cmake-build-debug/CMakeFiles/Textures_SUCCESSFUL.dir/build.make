# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/natalie/Downloads/clion-2018.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/natalie/Downloads/clion-2018.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6/cmake-build-debug

# Utility rule file for Textures_SUCCESSFUL.

# Include the progress variables for this target.
include CMakeFiles/Textures_SUCCESSFUL.dir/progress.make

CMakeFiles/Textures_SUCCESSFUL: Textures
	/home/natalie/Downloads/clion-2018.2.2/bin/cmake/linux/bin/cmake -E copy_directory /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6/shaders/ /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6/cmake-build-debug/shaders
	/home/natalie/Downloads/clion-2018.2.2/bin/cmake/linux/bin/cmake -E echo 
	/home/natalie/Downloads/clion-2018.2.2/bin/cmake/linux/bin/cmake -E echo =====================
	/home/natalie/Downloads/clion-2018.2.2/bin/cmake/linux/bin/cmake -E echo \ \ Compile\ complete!
	/home/natalie/Downloads/clion-2018.2.2/bin/cmake/linux/bin/cmake -E echo =====================
	/home/natalie/Downloads/clion-2018.2.2/bin/cmake/linux/bin/cmake -E echo /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6/cmake-build-debug

Textures_SUCCESSFUL: CMakeFiles/Textures_SUCCESSFUL
Textures_SUCCESSFUL: CMakeFiles/Textures_SUCCESSFUL.dir/build.make

.PHONY : Textures_SUCCESSFUL

# Rule to build all files generated by this target.
CMakeFiles/Textures_SUCCESSFUL.dir/build: Textures_SUCCESSFUL

.PHONY : CMakeFiles/Textures_SUCCESSFUL.dir/build

CMakeFiles/Textures_SUCCESSFUL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Textures_SUCCESSFUL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Textures_SUCCESSFUL.dir/clean

CMakeFiles/Textures_SUCCESSFUL.dir/depend:
	cd /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6 /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6 /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6/cmake-build-debug /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6/cmake-build-debug /home/natalie/workspaces/cs480Arnold/computer-graphics/PA6/cmake-build-debug/CMakeFiles/Textures_SUCCESSFUL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Textures_SUCCESSFUL.dir/depend

