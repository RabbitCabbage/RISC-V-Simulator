# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/untitled4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled4.dir/flags.make

CMakeFiles/untitled4.dir/src_seq.cpp.o: CMakeFiles/untitled4.dir/flags.make
CMakeFiles/untitled4.dir/src_seq.cpp.o: ../src_seq.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/untitled4.dir/src_seq.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled4.dir/src_seq.cpp.o -c "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/src_seq.cpp"

CMakeFiles/untitled4.dir/src_seq.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled4.dir/src_seq.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/src_seq.cpp" > CMakeFiles/untitled4.dir/src_seq.cpp.i

CMakeFiles/untitled4.dir/src_seq.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled4.dir/src_seq.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/src_seq.cpp" -o CMakeFiles/untitled4.dir/src_seq.cpp.s

# Object files for target untitled4
untitled4_OBJECTS = \
"CMakeFiles/untitled4.dir/src_seq.cpp.o"

# External object files for target untitled4
untitled4_EXTERNAL_OBJECTS =

untitled4: CMakeFiles/untitled4.dir/src_seq.cpp.o
untitled4: CMakeFiles/untitled4.dir/build.make
untitled4: CMakeFiles/untitled4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable untitled4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled4.dir/build: untitled4

.PHONY : CMakeFiles/untitled4.dir/build

CMakeFiles/untitled4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled4.dir/clean

CMakeFiles/untitled4.dir/depend:
	cd "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/cmake-build-debug" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/cmake-build-debug" "/mnt/c/Users/lu'ren'jia'd's/CLionProjects/risc-v32I/cmake-build-debug/CMakeFiles/untitled4.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/untitled4.dir/depend

