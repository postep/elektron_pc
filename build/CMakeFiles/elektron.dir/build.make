# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/postep/Pulpit/elektron_stm/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/postep/Pulpit/elektron_stm/build

# Include any dependencies generated for this target.
include CMakeFiles/elektron.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/elektron.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/elektron.dir/flags.make

CMakeFiles/elektron.dir/elektron4.cpp.o: CMakeFiles/elektron.dir/flags.make
CMakeFiles/elektron.dir/elektron4.cpp.o: /home/postep/Pulpit/elektron_stm/src/elektron4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/postep/Pulpit/elektron_stm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/elektron.dir/elektron4.cpp.o"
	/usr/bin/g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/elektron.dir/elektron4.cpp.o -c /home/postep/Pulpit/elektron_stm/src/elektron4.cpp

CMakeFiles/elektron.dir/elektron4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/elektron.dir/elektron4.cpp.i"
	/usr/bin/g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/postep/Pulpit/elektron_stm/src/elektron4.cpp > CMakeFiles/elektron.dir/elektron4.cpp.i

CMakeFiles/elektron.dir/elektron4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/elektron.dir/elektron4.cpp.s"
	/usr/bin/g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/postep/Pulpit/elektron_stm/src/elektron4.cpp -o CMakeFiles/elektron.dir/elektron4.cpp.s

CMakeFiles/elektron.dir/elektron4.cpp.o.requires:

.PHONY : CMakeFiles/elektron.dir/elektron4.cpp.o.requires

CMakeFiles/elektron.dir/elektron4.cpp.o.provides: CMakeFiles/elektron.dir/elektron4.cpp.o.requires
	$(MAKE) -f CMakeFiles/elektron.dir/build.make CMakeFiles/elektron.dir/elektron4.cpp.o.provides.build
.PHONY : CMakeFiles/elektron.dir/elektron4.cpp.o.provides

CMakeFiles/elektron.dir/elektron4.cpp.o.provides.build: CMakeFiles/elektron.dir/elektron4.cpp.o


CMakeFiles/elektron.dir/communicationbuffer.cpp.o: CMakeFiles/elektron.dir/flags.make
CMakeFiles/elektron.dir/communicationbuffer.cpp.o: /home/postep/Pulpit/elektron_stm/src/communicationbuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/postep/Pulpit/elektron_stm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/elektron.dir/communicationbuffer.cpp.o"
	/usr/bin/g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/elektron.dir/communicationbuffer.cpp.o -c /home/postep/Pulpit/elektron_stm/src/communicationbuffer.cpp

CMakeFiles/elektron.dir/communicationbuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/elektron.dir/communicationbuffer.cpp.i"
	/usr/bin/g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/postep/Pulpit/elektron_stm/src/communicationbuffer.cpp > CMakeFiles/elektron.dir/communicationbuffer.cpp.i

CMakeFiles/elektron.dir/communicationbuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/elektron.dir/communicationbuffer.cpp.s"
	/usr/bin/g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/postep/Pulpit/elektron_stm/src/communicationbuffer.cpp -o CMakeFiles/elektron.dir/communicationbuffer.cpp.s

CMakeFiles/elektron.dir/communicationbuffer.cpp.o.requires:

.PHONY : CMakeFiles/elektron.dir/communicationbuffer.cpp.o.requires

CMakeFiles/elektron.dir/communicationbuffer.cpp.o.provides: CMakeFiles/elektron.dir/communicationbuffer.cpp.o.requires
	$(MAKE) -f CMakeFiles/elektron.dir/build.make CMakeFiles/elektron.dir/communicationbuffer.cpp.o.provides.build
.PHONY : CMakeFiles/elektron.dir/communicationbuffer.cpp.o.provides

CMakeFiles/elektron.dir/communicationbuffer.cpp.o.provides.build: CMakeFiles/elektron.dir/communicationbuffer.cpp.o


CMakeFiles/elektron.dir/timer.cpp.o: CMakeFiles/elektron.dir/flags.make
CMakeFiles/elektron.dir/timer.cpp.o: /home/postep/Pulpit/elektron_stm/src/timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/postep/Pulpit/elektron_stm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/elektron.dir/timer.cpp.o"
	/usr/bin/g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/elektron.dir/timer.cpp.o -c /home/postep/Pulpit/elektron_stm/src/timer.cpp

CMakeFiles/elektron.dir/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/elektron.dir/timer.cpp.i"
	/usr/bin/g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/postep/Pulpit/elektron_stm/src/timer.cpp > CMakeFiles/elektron.dir/timer.cpp.i

CMakeFiles/elektron.dir/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/elektron.dir/timer.cpp.s"
	/usr/bin/g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/postep/Pulpit/elektron_stm/src/timer.cpp -o CMakeFiles/elektron.dir/timer.cpp.s

CMakeFiles/elektron.dir/timer.cpp.o.requires:

.PHONY : CMakeFiles/elektron.dir/timer.cpp.o.requires

CMakeFiles/elektron.dir/timer.cpp.o.provides: CMakeFiles/elektron.dir/timer.cpp.o.requires
	$(MAKE) -f CMakeFiles/elektron.dir/build.make CMakeFiles/elektron.dir/timer.cpp.o.provides.build
.PHONY : CMakeFiles/elektron.dir/timer.cpp.o.provides

CMakeFiles/elektron.dir/timer.cpp.o.provides.build: CMakeFiles/elektron.dir/timer.cpp.o


# Object files for target elektron
elektron_OBJECTS = \
"CMakeFiles/elektron.dir/elektron4.cpp.o" \
"CMakeFiles/elektron.dir/communicationbuffer.cpp.o" \
"CMakeFiles/elektron.dir/timer.cpp.o"

# External object files for target elektron
elektron_EXTERNAL_OBJECTS =

elektron: CMakeFiles/elektron.dir/elektron4.cpp.o
elektron: CMakeFiles/elektron.dir/communicationbuffer.cpp.o
elektron: CMakeFiles/elektron.dir/timer.cpp.o
elektron: CMakeFiles/elektron.dir/build.make
elektron: CMakeFiles/elektron.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/postep/Pulpit/elektron_stm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable elektron"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/elektron.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/elektron.dir/build: elektron

.PHONY : CMakeFiles/elektron.dir/build

CMakeFiles/elektron.dir/requires: CMakeFiles/elektron.dir/elektron4.cpp.o.requires
CMakeFiles/elektron.dir/requires: CMakeFiles/elektron.dir/communicationbuffer.cpp.o.requires
CMakeFiles/elektron.dir/requires: CMakeFiles/elektron.dir/timer.cpp.o.requires

.PHONY : CMakeFiles/elektron.dir/requires

CMakeFiles/elektron.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/elektron.dir/cmake_clean.cmake
.PHONY : CMakeFiles/elektron.dir/clean

CMakeFiles/elektron.dir/depend:
	cd /home/postep/Pulpit/elektron_stm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/postep/Pulpit/elektron_stm/src /home/postep/Pulpit/elektron_stm/src /home/postep/Pulpit/elektron_stm/build /home/postep/Pulpit/elektron_stm/build /home/postep/Pulpit/elektron_stm/build/CMakeFiles/elektron.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/elektron.dir/depend
