# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\86151\CLionProjects\untitled

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\86151\CLionProjects\untitled\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Slot.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Slot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Slot.dir/flags.make

CMakeFiles/Slot.dir/DataStructures/Slot.cpp.obj: CMakeFiles/Slot.dir/flags.make
CMakeFiles/Slot.dir/DataStructures/Slot.cpp.obj: ../DataStructures/Slot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\86151\CLionProjects\untitled\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Slot.dir/DataStructures/Slot.cpp.obj"
	C:\Users\86151\Desktop\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Slot.dir\DataStructures\Slot.cpp.obj -c C:\Users\86151\CLionProjects\untitled\DataStructures\Slot.cpp

CMakeFiles/Slot.dir/DataStructures/Slot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Slot.dir/DataStructures/Slot.cpp.i"
	C:\Users\86151\Desktop\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\86151\CLionProjects\untitled\DataStructures\Slot.cpp > CMakeFiles\Slot.dir\DataStructures\Slot.cpp.i

CMakeFiles/Slot.dir/DataStructures/Slot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Slot.dir/DataStructures/Slot.cpp.s"
	C:\Users\86151\Desktop\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\86151\CLionProjects\untitled\DataStructures\Slot.cpp -o CMakeFiles\Slot.dir\DataStructures\Slot.cpp.s

# Object files for target Slot
Slot_OBJECTS = \
"CMakeFiles/Slot.dir/DataStructures/Slot.cpp.obj"

# External object files for target Slot
Slot_EXTERNAL_OBJECTS =

Slot.exe: CMakeFiles/Slot.dir/DataStructures/Slot.cpp.obj
Slot.exe: CMakeFiles/Slot.dir/build.make
Slot.exe: CMakeFiles/Slot.dir/linklibs.rsp
Slot.exe: CMakeFiles/Slot.dir/objects1.rsp
Slot.exe: CMakeFiles/Slot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\86151\CLionProjects\untitled\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Slot.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Slot.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Slot.dir/build: Slot.exe
.PHONY : CMakeFiles/Slot.dir/build

CMakeFiles/Slot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Slot.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Slot.dir/clean

CMakeFiles/Slot.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\86151\CLionProjects\untitled C:\Users\86151\CLionProjects\untitled C:\Users\86151\CLionProjects\untitled\cmake-build-debug C:\Users\86151\CLionProjects\untitled\cmake-build-debug C:\Users\86151\CLionProjects\untitled\cmake-build-debug\CMakeFiles\Slot.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Slot.dir/depend
