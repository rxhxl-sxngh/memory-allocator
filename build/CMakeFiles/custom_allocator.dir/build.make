# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rsing/OSProj2-main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rsing/OSProj2-main/build

# Include any dependencies generated for this target.
include CMakeFiles/custom_allocator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/custom_allocator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/custom_allocator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/custom_allocator.dir/flags.make

CMakeFiles/custom_allocator.dir/src/main.c.o: CMakeFiles/custom_allocator.dir/flags.make
CMakeFiles/custom_allocator.dir/src/main.c.o: ../src/main.c
CMakeFiles/custom_allocator.dir/src/main.c.o: CMakeFiles/custom_allocator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rsing/OSProj2-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/custom_allocator.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/custom_allocator.dir/src/main.c.o -MF CMakeFiles/custom_allocator.dir/src/main.c.o.d -o CMakeFiles/custom_allocator.dir/src/main.c.o -c /home/rsing/OSProj2-main/src/main.c

CMakeFiles/custom_allocator.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/custom_allocator.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rsing/OSProj2-main/src/main.c > CMakeFiles/custom_allocator.dir/src/main.c.i

CMakeFiles/custom_allocator.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/custom_allocator.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rsing/OSProj2-main/src/main.c -o CMakeFiles/custom_allocator.dir/src/main.c.s

CMakeFiles/custom_allocator.dir/src/alloc.c.o: CMakeFiles/custom_allocator.dir/flags.make
CMakeFiles/custom_allocator.dir/src/alloc.c.o: ../src/alloc.c
CMakeFiles/custom_allocator.dir/src/alloc.c.o: CMakeFiles/custom_allocator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rsing/OSProj2-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/custom_allocator.dir/src/alloc.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/custom_allocator.dir/src/alloc.c.o -MF CMakeFiles/custom_allocator.dir/src/alloc.c.o.d -o CMakeFiles/custom_allocator.dir/src/alloc.c.o -c /home/rsing/OSProj2-main/src/alloc.c

CMakeFiles/custom_allocator.dir/src/alloc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/custom_allocator.dir/src/alloc.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rsing/OSProj2-main/src/alloc.c > CMakeFiles/custom_allocator.dir/src/alloc.c.i

CMakeFiles/custom_allocator.dir/src/alloc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/custom_allocator.dir/src/alloc.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rsing/OSProj2-main/src/alloc.c -o CMakeFiles/custom_allocator.dir/src/alloc.c.s

# Object files for target custom_allocator
custom_allocator_OBJECTS = \
"CMakeFiles/custom_allocator.dir/src/main.c.o" \
"CMakeFiles/custom_allocator.dir/src/alloc.c.o"

# External object files for target custom_allocator
custom_allocator_EXTERNAL_OBJECTS =

custom_allocator: CMakeFiles/custom_allocator.dir/src/main.c.o
custom_allocator: CMakeFiles/custom_allocator.dir/src/alloc.c.o
custom_allocator: CMakeFiles/custom_allocator.dir/build.make
custom_allocator: CMakeFiles/custom_allocator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rsing/OSProj2-main/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable custom_allocator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/custom_allocator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/custom_allocator.dir/build: custom_allocator
.PHONY : CMakeFiles/custom_allocator.dir/build

CMakeFiles/custom_allocator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/custom_allocator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/custom_allocator.dir/clean

CMakeFiles/custom_allocator.dir/depend:
	cd /home/rsing/OSProj2-main/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rsing/OSProj2-main /home/rsing/OSProj2-main /home/rsing/OSProj2-main/build /home/rsing/OSProj2-main/build /home/rsing/OSProj2-main/build/CMakeFiles/custom_allocator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/custom_allocator.dir/depend

