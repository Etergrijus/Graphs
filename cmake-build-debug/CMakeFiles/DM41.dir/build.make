# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/DM41.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DM41.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DM41.dir/flags.make

CMakeFiles/DM41.dir/main.cpp.obj: CMakeFiles/DM41.dir/flags.make
CMakeFiles/DM41.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DM41.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\DM41.dir\main.cpp.obj -c "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\main.cpp"

CMakeFiles/DM41.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DM41.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\main.cpp" > CMakeFiles\DM41.dir\main.cpp.i

CMakeFiles/DM41.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DM41.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\main.cpp" -o CMakeFiles\DM41.dir\main.cpp.s

CMakeFiles/DM41.dir/graph.cpp.obj: CMakeFiles/DM41.dir/flags.make
CMakeFiles/DM41.dir/graph.cpp.obj: ../graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DM41.dir/graph.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\DM41.dir\graph.cpp.obj -c "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\graph.cpp"

CMakeFiles/DM41.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DM41.dir/graph.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\graph.cpp" > CMakeFiles\DM41.dir\graph.cpp.i

CMakeFiles/DM41.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DM41.dir/graph.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\graph.cpp" -o CMakeFiles\DM41.dir\graph.cpp.s

# Object files for target DM41
DM41_OBJECTS = \
"CMakeFiles/DM41.dir/main.cpp.obj" \
"CMakeFiles/DM41.dir/graph.cpp.obj"

# External object files for target DM41
DM41_EXTERNAL_OBJECTS =

DM41.exe: CMakeFiles/DM41.dir/main.cpp.obj
DM41.exe: CMakeFiles/DM41.dir/graph.cpp.obj
DM41.exe: CMakeFiles/DM41.dir/build.make
DM41.exe: CMakeFiles/DM41.dir/linklibs.rsp
DM41.exe: CMakeFiles/DM41.dir/objects1.rsp
DM41.exe: CMakeFiles/DM41.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable DM41.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\DM41.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DM41.dir/build: DM41.exe

.PHONY : CMakeFiles/DM41.dir/build

CMakeFiles/DM41.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\DM41.dir\cmake_clean.cmake
.PHONY : CMakeFiles/DM41.dir/clean

CMakeFiles/DM41.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41" "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41" "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\cmake-build-debug" "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\cmake-build-debug" "C:\Program Files\JetBrains\CLion 2020.1\CLionProjects\DM41\cmake-build-debug\CMakeFiles\DM41.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/DM41.dir/depend

