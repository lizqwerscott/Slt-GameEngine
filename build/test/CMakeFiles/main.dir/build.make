# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lscott/Documents/Projrect/Slt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lscott/Documents/Projrect/Slt/build

# Include any dependencies generated for this target.
include test/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/main.dir/flags.make

test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o: test/CMakeFiles/main.dir/flags.make
test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o: ../test/BreakoutScene/MyBreakoutScene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lscott/Documents/Projrect/Slt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o"
	cd /home/lscott/Documents/Projrect/Slt/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o -c /home/lscott/Documents/Projrect/Slt/test/BreakoutScene/MyBreakoutScene.cpp

test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.i"
	cd /home/lscott/Documents/Projrect/Slt/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lscott/Documents/Projrect/Slt/test/BreakoutScene/MyBreakoutScene.cpp > CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.i

test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.s"
	cd /home/lscott/Documents/Projrect/Slt/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lscott/Documents/Projrect/Slt/test/BreakoutScene/MyBreakoutScene.cpp -o CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.s

test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o.requires:

.PHONY : test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o.requires

test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o.provides: test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/main.dir/build.make test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o.provides.build
.PHONY : test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o.provides

test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o.provides.build: test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o


test/CMakeFiles/main.dir/MyApplication.cpp.o: test/CMakeFiles/main.dir/flags.make
test/CMakeFiles/main.dir/MyApplication.cpp.o: ../test/MyApplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lscott/Documents/Projrect/Slt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/main.dir/MyApplication.cpp.o"
	cd /home/lscott/Documents/Projrect/Slt/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/MyApplication.cpp.o -c /home/lscott/Documents/Projrect/Slt/test/MyApplication.cpp

test/CMakeFiles/main.dir/MyApplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/MyApplication.cpp.i"
	cd /home/lscott/Documents/Projrect/Slt/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lscott/Documents/Projrect/Slt/test/MyApplication.cpp > CMakeFiles/main.dir/MyApplication.cpp.i

test/CMakeFiles/main.dir/MyApplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/MyApplication.cpp.s"
	cd /home/lscott/Documents/Projrect/Slt/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lscott/Documents/Projrect/Slt/test/MyApplication.cpp -o CMakeFiles/main.dir/MyApplication.cpp.s

test/CMakeFiles/main.dir/MyApplication.cpp.o.requires:

.PHONY : test/CMakeFiles/main.dir/MyApplication.cpp.o.requires

test/CMakeFiles/main.dir/MyApplication.cpp.o.provides: test/CMakeFiles/main.dir/MyApplication.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/main.dir/build.make test/CMakeFiles/main.dir/MyApplication.cpp.o.provides.build
.PHONY : test/CMakeFiles/main.dir/MyApplication.cpp.o.provides

test/CMakeFiles/main.dir/MyApplication.cpp.o.provides.build: test/CMakeFiles/main.dir/MyApplication.cpp.o


test/CMakeFiles/main.dir/mainTest.cpp.o: test/CMakeFiles/main.dir/flags.make
test/CMakeFiles/main.dir/mainTest.cpp.o: ../test/mainTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lscott/Documents/Projrect/Slt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/main.dir/mainTest.cpp.o"
	cd /home/lscott/Documents/Projrect/Slt/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/mainTest.cpp.o -c /home/lscott/Documents/Projrect/Slt/test/mainTest.cpp

test/CMakeFiles/main.dir/mainTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/mainTest.cpp.i"
	cd /home/lscott/Documents/Projrect/Slt/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lscott/Documents/Projrect/Slt/test/mainTest.cpp > CMakeFiles/main.dir/mainTest.cpp.i

test/CMakeFiles/main.dir/mainTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/mainTest.cpp.s"
	cd /home/lscott/Documents/Projrect/Slt/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lscott/Documents/Projrect/Slt/test/mainTest.cpp -o CMakeFiles/main.dir/mainTest.cpp.s

test/CMakeFiles/main.dir/mainTest.cpp.o.requires:

.PHONY : test/CMakeFiles/main.dir/mainTest.cpp.o.requires

test/CMakeFiles/main.dir/mainTest.cpp.o.provides: test/CMakeFiles/main.dir/mainTest.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/main.dir/build.make test/CMakeFiles/main.dir/mainTest.cpp.o.provides.build
.PHONY : test/CMakeFiles/main.dir/mainTest.cpp.o.provides

test/CMakeFiles/main.dir/mainTest.cpp.o.provides.build: test/CMakeFiles/main.dir/mainTest.cpp.o


# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o" \
"CMakeFiles/main.dir/MyApplication.cpp.o" \
"CMakeFiles/main.dir/mainTest.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

bin/main: test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o
bin/main: test/CMakeFiles/main.dir/MyApplication.cpp.o
bin/main: test/CMakeFiles/main.dir/mainTest.cpp.o
bin/main: test/CMakeFiles/main.dir/build.make
bin/main: src/libslt.a
bin/main: test/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lscott/Documents/Projrect/Slt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/main"
	cd /home/lscott/Documents/Projrect/Slt/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/main.dir/build: bin/main

.PHONY : test/CMakeFiles/main.dir/build

test/CMakeFiles/main.dir/requires: test/CMakeFiles/main.dir/BreakoutScene/MyBreakoutScene.cpp.o.requires
test/CMakeFiles/main.dir/requires: test/CMakeFiles/main.dir/MyApplication.cpp.o.requires
test/CMakeFiles/main.dir/requires: test/CMakeFiles/main.dir/mainTest.cpp.o.requires

.PHONY : test/CMakeFiles/main.dir/requires

test/CMakeFiles/main.dir/clean:
	cd /home/lscott/Documents/Projrect/Slt/build/test && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/main.dir/clean

test/CMakeFiles/main.dir/depend:
	cd /home/lscott/Documents/Projrect/Slt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lscott/Documents/Projrect/Slt /home/lscott/Documents/Projrect/Slt/test /home/lscott/Documents/Projrect/Slt/build /home/lscott/Documents/Projrect/Slt/build/test /home/lscott/Documents/Projrect/Slt/build/test/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/main.dir/depend

