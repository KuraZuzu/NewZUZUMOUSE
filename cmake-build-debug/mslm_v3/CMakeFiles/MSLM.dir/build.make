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

# Include any dependencies generated for this target.
include mslm_v3/CMakeFiles/MSLM.dir/depend.make

# Include the progress variables for this target.
include mslm_v3/CMakeFiles/MSLM.dir/progress.make

# Include the compile flags for this target's objects.
include mslm_v3/CMakeFiles/MSLM.dir/flags.make

mslm_v3/CMakeFiles/MSLM.dir/Motor.cpp.obj: mslm_v3/CMakeFiles/MSLM.dir/flags.make
mslm_v3/CMakeFiles/MSLM.dir/Motor.cpp.obj: ../mslm_v3/Motor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mslm_v3/CMakeFiles/MSLM.dir/Motor.cpp.obj"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MSLM.dir/Motor.cpp.obj -c /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/Motor.cpp

mslm_v3/CMakeFiles/MSLM.dir/Motor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MSLM.dir/Motor.cpp.i"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/Motor.cpp > CMakeFiles/MSLM.dir/Motor.cpp.i

mslm_v3/CMakeFiles/MSLM.dir/Motor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MSLM.dir/Motor.cpp.s"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/Motor.cpp -o CMakeFiles/MSLM.dir/Motor.cpp.s

mslm_v3/CMakeFiles/MSLM.dir/sensor.cpp.obj: mslm_v3/CMakeFiles/MSLM.dir/flags.make
mslm_v3/CMakeFiles/MSLM.dir/sensor.cpp.obj: ../mslm_v3/sensor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object mslm_v3/CMakeFiles/MSLM.dir/sensor.cpp.obj"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MSLM.dir/sensor.cpp.obj -c /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/sensor.cpp

mslm_v3/CMakeFiles/MSLM.dir/sensor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MSLM.dir/sensor.cpp.i"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/sensor.cpp > CMakeFiles/MSLM.dir/sensor.cpp.i

mslm_v3/CMakeFiles/MSLM.dir/sensor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MSLM.dir/sensor.cpp.s"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/sensor.cpp -o CMakeFiles/MSLM.dir/sensor.cpp.s

mslm_v3/CMakeFiles/MSLM.dir/vector.cpp.obj: mslm_v3/CMakeFiles/MSLM.dir/flags.make
mslm_v3/CMakeFiles/MSLM.dir/vector.cpp.obj: ../mslm_v3/vector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object mslm_v3/CMakeFiles/MSLM.dir/vector.cpp.obj"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MSLM.dir/vector.cpp.obj -c /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/vector.cpp

mslm_v3/CMakeFiles/MSLM.dir/vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MSLM.dir/vector.cpp.i"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/vector.cpp > CMakeFiles/MSLM.dir/vector.cpp.i

mslm_v3/CMakeFiles/MSLM.dir/vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MSLM.dir/vector.cpp.s"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/vector.cpp -o CMakeFiles/MSLM.dir/vector.cpp.s

mslm_v3/CMakeFiles/MSLM.dir/block.cpp.obj: mslm_v3/CMakeFiles/MSLM.dir/flags.make
mslm_v3/CMakeFiles/MSLM.dir/block.cpp.obj: ../mslm_v3/block.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object mslm_v3/CMakeFiles/MSLM.dir/block.cpp.obj"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MSLM.dir/block.cpp.obj -c /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/block.cpp

mslm_v3/CMakeFiles/MSLM.dir/block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MSLM.dir/block.cpp.i"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/block.cpp > CMakeFiles/MSLM.dir/block.cpp.i

mslm_v3/CMakeFiles/MSLM.dir/block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MSLM.dir/block.cpp.s"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/block.cpp -o CMakeFiles/MSLM.dir/block.cpp.s

mslm_v3/CMakeFiles/MSLM.dir/map3.cpp.obj: mslm_v3/CMakeFiles/MSLM.dir/flags.make
mslm_v3/CMakeFiles/MSLM.dir/map3.cpp.obj: ../mslm_v3/map3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object mslm_v3/CMakeFiles/MSLM.dir/map3.cpp.obj"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MSLM.dir/map3.cpp.obj -c /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/map3.cpp

mslm_v3/CMakeFiles/MSLM.dir/map3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MSLM.dir/map3.cpp.i"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/map3.cpp > CMakeFiles/MSLM.dir/map3.cpp.i

mslm_v3/CMakeFiles/MSLM.dir/map3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MSLM.dir/map3.cpp.s"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/map3.cpp -o CMakeFiles/MSLM.dir/map3.cpp.s

mslm_v3/CMakeFiles/MSLM.dir/Point.cpp.obj: mslm_v3/CMakeFiles/MSLM.dir/flags.make
mslm_v3/CMakeFiles/MSLM.dir/Point.cpp.obj: ../mslm_v3/Point.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object mslm_v3/CMakeFiles/MSLM.dir/Point.cpp.obj"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MSLM.dir/Point.cpp.obj -c /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/Point.cpp

mslm_v3/CMakeFiles/MSLM.dir/Point.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MSLM.dir/Point.cpp.i"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/Point.cpp > CMakeFiles/MSLM.dir/Point.cpp.i

mslm_v3/CMakeFiles/MSLM.dir/Point.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MSLM.dir/Point.cpp.s"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/Point.cpp -o CMakeFiles/MSLM.dir/Point.cpp.s

mslm_v3/CMakeFiles/MSLM.dir/PositionEstimator.cpp.obj: mslm_v3/CMakeFiles/MSLM.dir/flags.make
mslm_v3/CMakeFiles/MSLM.dir/PositionEstimator.cpp.obj: ../mslm_v3/PositionEstimator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object mslm_v3/CMakeFiles/MSLM.dir/PositionEstimator.cpp.obj"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MSLM.dir/PositionEstimator.cpp.obj -c /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/PositionEstimator.cpp

mslm_v3/CMakeFiles/MSLM.dir/PositionEstimator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MSLM.dir/PositionEstimator.cpp.i"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/PositionEstimator.cpp > CMakeFiles/MSLM.dir/PositionEstimator.cpp.i

mslm_v3/CMakeFiles/MSLM.dir/PositionEstimator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MSLM.dir/PositionEstimator.cpp.s"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && /usr/local/bin/arm-none-eabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3/PositionEstimator.cpp -o CMakeFiles/MSLM.dir/PositionEstimator.cpp.s

# Object files for target MSLM
MSLM_OBJECTS = \
"CMakeFiles/MSLM.dir/Motor.cpp.obj" \
"CMakeFiles/MSLM.dir/sensor.cpp.obj" \
"CMakeFiles/MSLM.dir/vector.cpp.obj" \
"CMakeFiles/MSLM.dir/block.cpp.obj" \
"CMakeFiles/MSLM.dir/map3.cpp.obj" \
"CMakeFiles/MSLM.dir/Point.cpp.obj" \
"CMakeFiles/MSLM.dir/PositionEstimator.cpp.obj"

# External object files for target MSLM
MSLM_EXTERNAL_OBJECTS =

mslm_v3/libMSLM.a: mslm_v3/CMakeFiles/MSLM.dir/Motor.cpp.obj
mslm_v3/libMSLM.a: mslm_v3/CMakeFiles/MSLM.dir/sensor.cpp.obj
mslm_v3/libMSLM.a: mslm_v3/CMakeFiles/MSLM.dir/vector.cpp.obj
mslm_v3/libMSLM.a: mslm_v3/CMakeFiles/MSLM.dir/block.cpp.obj
mslm_v3/libMSLM.a: mslm_v3/CMakeFiles/MSLM.dir/map3.cpp.obj
mslm_v3/libMSLM.a: mslm_v3/CMakeFiles/MSLM.dir/Point.cpp.obj
mslm_v3/libMSLM.a: mslm_v3/CMakeFiles/MSLM.dir/PositionEstimator.cpp.obj
mslm_v3/libMSLM.a: mslm_v3/CMakeFiles/MSLM.dir/build.make
mslm_v3/libMSLM.a: mslm_v3/CMakeFiles/MSLM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libMSLM.a"
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && $(CMAKE_COMMAND) -P CMakeFiles/MSLM.dir/cmake_clean_target.cmake
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MSLM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mslm_v3/CMakeFiles/MSLM.dir/build: mslm_v3/libMSLM.a

.PHONY : mslm_v3/CMakeFiles/MSLM.dir/build

mslm_v3/CMakeFiles/MSLM.dir/clean:
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 && $(CMAKE_COMMAND) -P CMakeFiles/MSLM.dir/cmake_clean.cmake
.PHONY : mslm_v3/CMakeFiles/MSLM.dir/clean

mslm_v3/CMakeFiles/MSLM.dir/depend:
	cd /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zuzukun/CLionProjects/newzuzumouse /Users/zuzukun/CLionProjects/newzuzumouse/mslm_v3 /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3 /Users/zuzukun/CLionProjects/newzuzumouse/cmake-build-debug/mslm_v3/CMakeFiles/MSLM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mslm_v3/CMakeFiles/MSLM.dir/depend

