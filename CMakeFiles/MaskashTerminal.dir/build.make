# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marscat/mskT/MaskashTerminal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marscat/mskT/MaskashTerminal

# Include any dependencies generated for this target.
include CMakeFiles/MaskashTerminal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MaskashTerminal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MaskashTerminal.dir/flags.make

CMakeFiles/MaskashTerminal.dir/terminal.cpp.o: CMakeFiles/MaskashTerminal.dir/flags.make
CMakeFiles/MaskashTerminal.dir/terminal.cpp.o: terminal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marscat/mskT/MaskashTerminal/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MaskashTerminal.dir/terminal.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MaskashTerminal.dir/terminal.cpp.o -c /home/marscat/mskT/MaskashTerminal/terminal.cpp

CMakeFiles/MaskashTerminal.dir/terminal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MaskashTerminal.dir/terminal.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marscat/mskT/MaskashTerminal/terminal.cpp > CMakeFiles/MaskashTerminal.dir/terminal.cpp.i

CMakeFiles/MaskashTerminal.dir/terminal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MaskashTerminal.dir/terminal.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marscat/mskT/MaskashTerminal/terminal.cpp -o CMakeFiles/MaskashTerminal.dir/terminal.cpp.s

# Object files for target MaskashTerminal
MaskashTerminal_OBJECTS = \
"CMakeFiles/MaskashTerminal.dir/terminal.cpp.o"

# External object files for target MaskashTerminal
MaskashTerminal_EXTERNAL_OBJECTS =

MaskashTerminal: CMakeFiles/MaskashTerminal.dir/terminal.cpp.o
MaskashTerminal: CMakeFiles/MaskashTerminal.dir/build.make
MaskashTerminal: /usr/local/lib/libboost_program_options.so
MaskashTerminal: CMakeFiles/MaskashTerminal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marscat/mskT/MaskashTerminal/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MaskashTerminal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MaskashTerminal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MaskashTerminal.dir/build: MaskashTerminal

.PHONY : CMakeFiles/MaskashTerminal.dir/build

CMakeFiles/MaskashTerminal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MaskashTerminal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MaskashTerminal.dir/clean

CMakeFiles/MaskashTerminal.dir/depend:
	cd /home/marscat/mskT/MaskashTerminal && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marscat/mskT/MaskashTerminal /home/marscat/mskT/MaskashTerminal /home/marscat/mskT/MaskashTerminal /home/marscat/mskT/MaskashTerminal /home/marscat/mskT/MaskashTerminal/CMakeFiles/MaskashTerminal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MaskashTerminal.dir/depend

