# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures/build"

# Include any dependencies generated for this target.
include CMakeFiles/Test1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Test1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Test1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Test1.dir/flags.make

CMakeFiles/Test1.dir/test_rank_tree.cpp.obj: CMakeFiles/Test1.dir/flags.make
CMakeFiles/Test1.dir/test_rank_tree.cpp.obj: ../test_rank_tree.cpp
CMakeFiles/Test1.dir/test_rank_tree.cpp.obj: CMakeFiles/Test1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Test1.dir/test_rank_tree.cpp.obj"
	C:/TDM-GCC-64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Test1.dir/test_rank_tree.cpp.obj -MF CMakeFiles/Test1.dir/test_rank_tree.cpp.obj.d -o CMakeFiles/Test1.dir/test_rank_tree.cpp.obj -c "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures/test_rank_tree.cpp"

CMakeFiles/Test1.dir/test_rank_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test1.dir/test_rank_tree.cpp.i"
	C:/TDM-GCC-64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures/test_rank_tree.cpp" > CMakeFiles/Test1.dir/test_rank_tree.cpp.i

CMakeFiles/Test1.dir/test_rank_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test1.dir/test_rank_tree.cpp.s"
	C:/TDM-GCC-64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures/test_rank_tree.cpp" -o CMakeFiles/Test1.dir/test_rank_tree.cpp.s

# Object files for target Test1
Test1_OBJECTS = \
"CMakeFiles/Test1.dir/test_rank_tree.cpp.obj"

# External object files for target Test1
Test1_EXTERNAL_OBJECTS =

Test1.exe: CMakeFiles/Test1.dir/test_rank_tree.cpp.obj
Test1.exe: CMakeFiles/Test1.dir/build.make
Test1.exe: CMakeFiles/Test1.dir/linklibs.rsp
Test1.exe: CMakeFiles/Test1.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Test1.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/Test1.dir/objects.a
	C:/TDM-GCC-64/bin/ar.exe cr CMakeFiles/Test1.dir/objects.a @CMakeFiles/Test1.dir/objects1.rsp
	C:/TDM-GCC-64/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/Test1.dir/objects.a -Wl,--no-whole-archive -o Test1.exe -Wl,--out-implib,libTest1.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/Test1.dir/linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/Test1.dir/build: Test1.exe
.PHONY : CMakeFiles/Test1.dir/build

CMakeFiles/Test1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Test1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Test1.dir/clean

CMakeFiles/Test1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures" "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures" "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures/build" "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures/build" "C:/Users/itayl/OneDrive - Technion/Desktop/Semesters/semester_c/Mivni/Assignments/HW2_WET/HW2_DataStractures/build/CMakeFiles/Test1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Test1.dir/depend

