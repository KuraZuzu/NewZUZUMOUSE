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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zuzukun/CLionProjects/newzuzumouse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug

# Utility rule file for sercon.

# Include the progress variables for this target.
include CMakeFiles/sercon.dir/progress.make

CMakeFiles/sercon:
	command screen /dev/tty.usbmodem14202 9600

sercon: CMakeFiles/sercon
sercon: CMakeFiles/sercon.dir/build.make

.PHONY : sercon

# Rule to build all files generated by this target.
CMakeFiles/sercon.dir/build: sercon

.PHONY : CMakeFiles/sercon.dir/build

CMakeFiles/sercon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sercon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sercon.dir/clean

CMakeFiles/sercon.dir/depend:
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zuzukun/CLionProjects/newzuzumouse /Users/zuzukun/CLionProjects/newzuzumouse /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/CMakeFiles/sercon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sercon.dir/depend

