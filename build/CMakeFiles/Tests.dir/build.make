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
CMAKE_COMMAND = /home/aint/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/aint/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aint/park/algs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aint/park/algs/build

# Include any dependencies generated for this target.
include CMakeFiles/Tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tests.dir/flags.make

CMakeFiles/Tests.dir/IGraph/IGraph.cpp.o: CMakeFiles/Tests.dir/flags.make
CMakeFiles/Tests.dir/IGraph/IGraph.cpp.o: ../IGraph/IGraph.cpp
CMakeFiles/Tests.dir/IGraph/IGraph.cpp.o: CMakeFiles/Tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aint/park/algs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tests.dir/IGraph/IGraph.cpp.o"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tests.dir/IGraph/IGraph.cpp.o -MF CMakeFiles/Tests.dir/IGraph/IGraph.cpp.o.d -o CMakeFiles/Tests.dir/IGraph/IGraph.cpp.o -c /home/aint/park/algs/IGraph/IGraph.cpp

CMakeFiles/Tests.dir/IGraph/IGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/IGraph/IGraph.cpp.i"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aint/park/algs/IGraph/IGraph.cpp > CMakeFiles/Tests.dir/IGraph/IGraph.cpp.i

CMakeFiles/Tests.dir/IGraph/IGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/IGraph/IGraph.cpp.s"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aint/park/algs/IGraph/IGraph.cpp -o CMakeFiles/Tests.dir/IGraph/IGraph.cpp.s

CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.o: CMakeFiles/Tests.dir/flags.make
CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.o: ../ListGraph/ListGraph.cpp
CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.o: CMakeFiles/Tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aint/park/algs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.o"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.o -MF CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.o.d -o CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.o -c /home/aint/park/algs/ListGraph/ListGraph.cpp

CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.i"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aint/park/algs/ListGraph/ListGraph.cpp > CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.i

CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.s"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aint/park/algs/ListGraph/ListGraph.cpp -o CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.s

CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.o: CMakeFiles/Tests.dir/flags.make
CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.o: ../ArcGraph/ArcGraph.cpp
CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.o: CMakeFiles/Tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aint/park/algs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.o"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.o -MF CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.o.d -o CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.o -c /home/aint/park/algs/ArcGraph/ArcGraph.cpp

CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.i"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aint/park/algs/ArcGraph/ArcGraph.cpp > CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.i

CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.s"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aint/park/algs/ArcGraph/ArcGraph.cpp -o CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.s

CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.o: CMakeFiles/Tests.dir/flags.make
CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.o: ../MatrixGraph/MatrixGraph.cpp
CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.o: CMakeFiles/Tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aint/park/algs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.o"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.o -MF CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.o.d -o CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.o -c /home/aint/park/algs/MatrixGraph/MatrixGraph.cpp

CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.i"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aint/park/algs/MatrixGraph/MatrixGraph.cpp > CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.i

CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.s"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aint/park/algs/MatrixGraph/MatrixGraph.cpp -o CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.s

CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.o: CMakeFiles/Tests.dir/flags.make
CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.o: ../SetGraph/SetGraph.cpp
CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.o: CMakeFiles/Tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aint/park/algs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.o"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.o -MF CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.o.d -o CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.o -c /home/aint/park/algs/SetGraph/SetGraph.cpp

CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.i"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aint/park/algs/SetGraph/SetGraph.cpp > CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.i

CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.s"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aint/park/algs/SetGraph/SetGraph.cpp -o CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.s

CMakeFiles/Tests.dir/tests.cpp.o: CMakeFiles/Tests.dir/flags.make
CMakeFiles/Tests.dir/tests.cpp.o: ../tests.cpp
CMakeFiles/Tests.dir/tests.cpp.o: CMakeFiles/Tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aint/park/algs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Tests.dir/tests.cpp.o"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tests.dir/tests.cpp.o -MF CMakeFiles/Tests.dir/tests.cpp.o.d -o CMakeFiles/Tests.dir/tests.cpp.o -c /home/aint/park/algs/tests.cpp

CMakeFiles/Tests.dir/tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/tests.cpp.i"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aint/park/algs/tests.cpp > CMakeFiles/Tests.dir/tests.cpp.i

CMakeFiles/Tests.dir/tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/tests.cpp.s"
	/usr/share/clang/scan-build-10/libexec/c++-analyzer $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aint/park/algs/tests.cpp -o CMakeFiles/Tests.dir/tests.cpp.s

# Object files for target Tests
Tests_OBJECTS = \
"CMakeFiles/Tests.dir/IGraph/IGraph.cpp.o" \
"CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.o" \
"CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.o" \
"CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.o" \
"CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.o" \
"CMakeFiles/Tests.dir/tests.cpp.o"

# External object files for target Tests
Tests_EXTERNAL_OBJECTS =

Tests: CMakeFiles/Tests.dir/IGraph/IGraph.cpp.o
Tests: CMakeFiles/Tests.dir/ListGraph/ListGraph.cpp.o
Tests: CMakeFiles/Tests.dir/ArcGraph/ArcGraph.cpp.o
Tests: CMakeFiles/Tests.dir/MatrixGraph/MatrixGraph.cpp.o
Tests: CMakeFiles/Tests.dir/SetGraph/SetGraph.cpp.o
Tests: CMakeFiles/Tests.dir/tests.cpp.o
Tests: CMakeFiles/Tests.dir/build.make
Tests: /usr/local/lib/libgtest_main.a
Tests: /usr/local/lib/libgtest.a
Tests: CMakeFiles/Tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aint/park/algs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tests.dir/build: Tests
.PHONY : CMakeFiles/Tests.dir/build

CMakeFiles/Tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tests.dir/clean

CMakeFiles/Tests.dir/depend:
	cd /home/aint/park/algs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aint/park/algs /home/aint/park/algs /home/aint/park/algs/build /home/aint/park/algs/build /home/aint/park/algs/build/CMakeFiles/Tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tests.dir/depend

