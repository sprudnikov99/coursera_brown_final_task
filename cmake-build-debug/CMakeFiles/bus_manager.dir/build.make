# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sprudnikov99/CLionProjects/bus_manager

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sprudnikov99/CLionProjects/bus_manager/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bus_manager.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bus_manager.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bus_manager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bus_manager.dir/flags.make

CMakeFiles/bus_manager.dir/main.cpp.o: CMakeFiles/bus_manager.dir/flags.make
CMakeFiles/bus_manager.dir/main.cpp.o: ../main.cpp
CMakeFiles/bus_manager.dir/main.cpp.o: CMakeFiles/bus_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sprudnikov99/CLionProjects/bus_manager/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bus_manager.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bus_manager.dir/main.cpp.o -MF CMakeFiles/bus_manager.dir/main.cpp.o.d -o CMakeFiles/bus_manager.dir/main.cpp.o -c /Users/sprudnikov99/CLionProjects/bus_manager/main.cpp

CMakeFiles/bus_manager.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bus_manager.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sprudnikov99/CLionProjects/bus_manager/main.cpp > CMakeFiles/bus_manager.dir/main.cpp.i

CMakeFiles/bus_manager.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bus_manager.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sprudnikov99/CLionProjects/bus_manager/main.cpp -o CMakeFiles/bus_manager.dir/main.cpp.s

CMakeFiles/bus_manager.dir/bus_manager.cpp.o: CMakeFiles/bus_manager.dir/flags.make
CMakeFiles/bus_manager.dir/bus_manager.cpp.o: ../bus_manager.cpp
CMakeFiles/bus_manager.dir/bus_manager.cpp.o: CMakeFiles/bus_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sprudnikov99/CLionProjects/bus_manager/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bus_manager.dir/bus_manager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bus_manager.dir/bus_manager.cpp.o -MF CMakeFiles/bus_manager.dir/bus_manager.cpp.o.d -o CMakeFiles/bus_manager.dir/bus_manager.cpp.o -c /Users/sprudnikov99/CLionProjects/bus_manager/bus_manager.cpp

CMakeFiles/bus_manager.dir/bus_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bus_manager.dir/bus_manager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sprudnikov99/CLionProjects/bus_manager/bus_manager.cpp > CMakeFiles/bus_manager.dir/bus_manager.cpp.i

CMakeFiles/bus_manager.dir/bus_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bus_manager.dir/bus_manager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sprudnikov99/CLionProjects/bus_manager/bus_manager.cpp -o CMakeFiles/bus_manager.dir/bus_manager.cpp.s

CMakeFiles/bus_manager.dir/cache.cpp.o: CMakeFiles/bus_manager.dir/flags.make
CMakeFiles/bus_manager.dir/cache.cpp.o: ../cache.cpp
CMakeFiles/bus_manager.dir/cache.cpp.o: CMakeFiles/bus_manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sprudnikov99/CLionProjects/bus_manager/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bus_manager.dir/cache.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bus_manager.dir/cache.cpp.o -MF CMakeFiles/bus_manager.dir/cache.cpp.o.d -o CMakeFiles/bus_manager.dir/cache.cpp.o -c /Users/sprudnikov99/CLionProjects/bus_manager/cache.cpp

CMakeFiles/bus_manager.dir/cache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bus_manager.dir/cache.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sprudnikov99/CLionProjects/bus_manager/cache.cpp > CMakeFiles/bus_manager.dir/cache.cpp.i

CMakeFiles/bus_manager.dir/cache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bus_manager.dir/cache.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sprudnikov99/CLionProjects/bus_manager/cache.cpp -o CMakeFiles/bus_manager.dir/cache.cpp.s

# Object files for target bus_manager
bus_manager_OBJECTS = \
"CMakeFiles/bus_manager.dir/main.cpp.o" \
"CMakeFiles/bus_manager.dir/bus_manager.cpp.o" \
"CMakeFiles/bus_manager.dir/cache.cpp.o"

# External object files for target bus_manager
bus_manager_EXTERNAL_OBJECTS =

bus_manager: CMakeFiles/bus_manager.dir/main.cpp.o
bus_manager: CMakeFiles/bus_manager.dir/bus_manager.cpp.o
bus_manager: CMakeFiles/bus_manager.dir/cache.cpp.o
bus_manager: CMakeFiles/bus_manager.dir/build.make
bus_manager: CMakeFiles/bus_manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sprudnikov99/CLionProjects/bus_manager/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bus_manager"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bus_manager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bus_manager.dir/build: bus_manager
.PHONY : CMakeFiles/bus_manager.dir/build

CMakeFiles/bus_manager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bus_manager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bus_manager.dir/clean

CMakeFiles/bus_manager.dir/depend:
	cd /Users/sprudnikov99/CLionProjects/bus_manager/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sprudnikov99/CLionProjects/bus_manager /Users/sprudnikov99/CLionProjects/bus_manager /Users/sprudnikov99/CLionProjects/bus_manager/cmake-build-debug /Users/sprudnikov99/CLionProjects/bus_manager/cmake-build-debug /Users/sprudnikov99/CLionProjects/bus_manager/cmake-build-debug/CMakeFiles/bus_manager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bus_manager.dir/depend

