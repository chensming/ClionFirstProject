# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = "D:\CLion\CLion 2019.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion\CLion 2019.3.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\ClionProject\DSPHomework\LinkedStudent

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\ClionProject\DSPHomework\LinkedStudent\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LinkedStudent.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LinkedStudent.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LinkedStudent.dir/flags.make

CMakeFiles/LinkedStudent.dir/main.cpp.obj: CMakeFiles/LinkedStudent.dir/flags.make
CMakeFiles/LinkedStudent.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProject\DSPHomework\LinkedStudent\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LinkedStudent.dir/main.cpp.obj"
	C:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\LinkedStudent.dir\main.cpp.obj -c D:\ClionProject\DSPHomework\LinkedStudent\main.cpp

CMakeFiles/LinkedStudent.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LinkedStudent.dir/main.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProject\DSPHomework\LinkedStudent\main.cpp > CMakeFiles\LinkedStudent.dir\main.cpp.i

CMakeFiles/LinkedStudent.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LinkedStudent.dir/main.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProject\DSPHomework\LinkedStudent\main.cpp -o CMakeFiles\LinkedStudent.dir\main.cpp.s

CMakeFiles/LinkedStudent.dir/studentUnit.cpp.obj: CMakeFiles/LinkedStudent.dir/flags.make
CMakeFiles/LinkedStudent.dir/studentUnit.cpp.obj: ../studentUnit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProject\DSPHomework\LinkedStudent\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LinkedStudent.dir/studentUnit.cpp.obj"
	C:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\LinkedStudent.dir\studentUnit.cpp.obj -c D:\ClionProject\DSPHomework\LinkedStudent\studentUnit.cpp

CMakeFiles/LinkedStudent.dir/studentUnit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LinkedStudent.dir/studentUnit.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProject\DSPHomework\LinkedStudent\studentUnit.cpp > CMakeFiles\LinkedStudent.dir\studentUnit.cpp.i

CMakeFiles/LinkedStudent.dir/studentUnit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LinkedStudent.dir/studentUnit.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProject\DSPHomework\LinkedStudent\studentUnit.cpp -o CMakeFiles\LinkedStudent.dir\studentUnit.cpp.s

# Object files for target LinkedStudent
LinkedStudent_OBJECTS = \
"CMakeFiles/LinkedStudent.dir/main.cpp.obj" \
"CMakeFiles/LinkedStudent.dir/studentUnit.cpp.obj"

# External object files for target LinkedStudent
LinkedStudent_EXTERNAL_OBJECTS =

LinkedStudent.exe: CMakeFiles/LinkedStudent.dir/main.cpp.obj
LinkedStudent.exe: CMakeFiles/LinkedStudent.dir/studentUnit.cpp.obj
LinkedStudent.exe: CMakeFiles/LinkedStudent.dir/build.make
LinkedStudent.exe: CMakeFiles/LinkedStudent.dir/linklibs.rsp
LinkedStudent.exe: CMakeFiles/LinkedStudent.dir/objects1.rsp
LinkedStudent.exe: CMakeFiles/LinkedStudent.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\ClionProject\DSPHomework\LinkedStudent\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable LinkedStudent.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LinkedStudent.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LinkedStudent.dir/build: LinkedStudent.exe

.PHONY : CMakeFiles/LinkedStudent.dir/build

CMakeFiles/LinkedStudent.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LinkedStudent.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LinkedStudent.dir/clean

CMakeFiles/LinkedStudent.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\ClionProject\DSPHomework\LinkedStudent D:\ClionProject\DSPHomework\LinkedStudent D:\ClionProject\DSPHomework\LinkedStudent\cmake-build-debug D:\ClionProject\DSPHomework\LinkedStudent\cmake-build-debug D:\ClionProject\DSPHomework\LinkedStudent\cmake-build-debug\CMakeFiles\LinkedStudent.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LinkedStudent.dir/depend
