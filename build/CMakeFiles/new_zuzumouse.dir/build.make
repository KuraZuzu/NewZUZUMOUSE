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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zuzukun/CLionProjects/newzuzumouse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zuzukun/CLionProjects/newzuzumouse/build

# Include any dependencies generated for this target.
include CMakeFiles/new_zuzumouse.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/new_zuzumouse.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/new_zuzumouse.dir/flags.make

CMakeFiles/new_zuzumouse.dir/main.cpp.obj: CMakeFiles/new_zuzumouse.dir/flags.make
CMakeFiles/new_zuzumouse.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/new_zuzumouse.dir/main.cpp.obj"
	/usr/local/bin/arm-none-eabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/new_zuzumouse.dir/main.cpp.obj -c /Users/zuzukun/CLionProjects/newzuzumouse/main.cpp

CMakeFiles/new_zuzumouse.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/new_zuzumouse.dir/main.cpp.i"
	/usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zuzukun/CLionProjects/newzuzumouse/main.cpp > CMakeFiles/new_zuzumouse.dir/main.cpp.i

CMakeFiles/new_zuzumouse.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/new_zuzumouse.dir/main.cpp.s"
	/usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zuzukun/CLionProjects/newzuzumouse/main.cpp -o CMakeFiles/new_zuzumouse.dir/main.cpp.s

# Object files for target new_zuzumouse
new_zuzumouse_OBJECTS = \
"CMakeFiles/new_zuzumouse.dir/main.cpp.obj"

# External object files for target new_zuzumouse
new_zuzumouse_EXTERNAL_OBJECTS = \
"/Users/zuzukun/CLionProjects/newzuzumouse/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/startup_LPC17xx.o" \
"/Users/zuzukun/CLionProjects/newzuzumouse/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/system_LPC17xx.o" \
"/Users/zuzukun/CLionProjects/newzuzumouse/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/cmsis_nvic.o" \
"/Users/zuzukun/CLionProjects/newzuzumouse/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/retarget.o" \
"/Users/zuzukun/CLionProjects/newzuzumouse/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/board.o"

new_zuzumouse: CMakeFiles/new_zuzumouse.dir/main.cpp.obj
new_zuzumouse: ../mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/startup_LPC17xx.o
new_zuzumouse: ../mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/system_LPC17xx.o
new_zuzumouse: ../mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/cmsis_nvic.o
new_zuzumouse: ../mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/retarget.o
new_zuzumouse: ../mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/board.o
new_zuzumouse: CMakeFiles/new_zuzumouse.dir/build.make
new_zuzumouse: MSLMv3/libMSLM.a
new_zuzumouse: CMakeFiles/new_zuzumouse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable new_zuzumouse"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/new_zuzumouse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/new_zuzumouse.dir/build: new_zuzumouse

.PHONY : CMakeFiles/new_zuzumouse.dir/build

CMakeFiles/new_zuzumouse.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/new_zuzumouse.dir/cmake_clean.cmake
.PHONY : CMakeFiles/new_zuzumouse.dir/clean

CMakeFiles/new_zuzumouse.dir/depend:
	cd /Users/zuzukun/CLionProjects/newzuzumouse/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zuzukun/CLionProjects/newzuzumouse /Users/zuzukun/CLionProjects/newzuzumouse /Users/zuzukun/CLionProjects/newzuzumouse/build /Users/zuzukun/CLionProjects/newzuzumouse/build /Users/zuzukun/CLionProjects/newzuzumouse/build/CMakeFiles/new_zuzumouse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/new_zuzumouse.dir/depend

