# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.13.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.13.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/saujasvs/Documents/spring2019/graphics/assignment_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build

# Include any dependencies generated for this target.
include external/glfw-3.1.2/examples/CMakeFiles/boing.dir/depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/examples/CMakeFiles/boing.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/examples/CMakeFiles/boing.dir/flags.make

external/glfw-3.1.2/examples/CMakeFiles/boing.dir/boing.c.o: external/glfw-3.1.2/examples/CMakeFiles/boing.dir/flags.make
external/glfw-3.1.2/examples/CMakeFiles/boing.dir/boing.c.o: ../external/glfw-3.1.2/examples/boing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/saujasvs/Documents/spring2019/graphics/assignment_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/examples/CMakeFiles/boing.dir/boing.c.o"
	cd /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build/external/glfw-3.1.2/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/boing.dir/boing.c.o   -c /Users/saujasvs/Documents/spring2019/graphics/assignment_2/external/glfw-3.1.2/examples/boing.c

external/glfw-3.1.2/examples/CMakeFiles/boing.dir/boing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/boing.dir/boing.c.i"
	cd /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build/external/glfw-3.1.2/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/saujasvs/Documents/spring2019/graphics/assignment_2/external/glfw-3.1.2/examples/boing.c > CMakeFiles/boing.dir/boing.c.i

external/glfw-3.1.2/examples/CMakeFiles/boing.dir/boing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/boing.dir/boing.c.s"
	cd /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build/external/glfw-3.1.2/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/saujasvs/Documents/spring2019/graphics/assignment_2/external/glfw-3.1.2/examples/boing.c -o CMakeFiles/boing.dir/boing.c.s

# Object files for target boing
boing_OBJECTS = \
"CMakeFiles/boing.dir/boing.c.o"

# External object files for target boing
boing_EXTERNAL_OBJECTS =

external/glfw-3.1.2/examples/boing.app/Contents/MacOS/boing: external/glfw-3.1.2/examples/CMakeFiles/boing.dir/boing.c.o
external/glfw-3.1.2/examples/boing.app/Contents/MacOS/boing: external/glfw-3.1.2/examples/CMakeFiles/boing.dir/build.make
external/glfw-3.1.2/examples/boing.app/Contents/MacOS/boing: external/glfw-3.1.2/src/libglfw3.a
external/glfw-3.1.2/examples/boing.app/Contents/MacOS/boing: external/glfw-3.1.2/examples/CMakeFiles/boing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/saujasvs/Documents/spring2019/graphics/assignment_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable boing.app/Contents/MacOS/boing"
	cd /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build/external/glfw-3.1.2/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/boing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/examples/CMakeFiles/boing.dir/build: external/glfw-3.1.2/examples/boing.app/Contents/MacOS/boing

.PHONY : external/glfw-3.1.2/examples/CMakeFiles/boing.dir/build

external/glfw-3.1.2/examples/CMakeFiles/boing.dir/clean:
	cd /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build/external/glfw-3.1.2/examples && $(CMAKE_COMMAND) -P CMakeFiles/boing.dir/cmake_clean.cmake
.PHONY : external/glfw-3.1.2/examples/CMakeFiles/boing.dir/clean

external/glfw-3.1.2/examples/CMakeFiles/boing.dir/depend:
	cd /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/saujasvs/Documents/spring2019/graphics/assignment_2 /Users/saujasvs/Documents/spring2019/graphics/assignment_2/external/glfw-3.1.2/examples /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build/external/glfw-3.1.2/examples /Users/saujasvs/Documents/spring2019/graphics/assignment_2/build/external/glfw-3.1.2/examples/CMakeFiles/boing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/examples/CMakeFiles/boing.dir/depend

