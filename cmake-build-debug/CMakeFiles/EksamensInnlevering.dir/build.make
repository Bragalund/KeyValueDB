# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/bragalund/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/172.4343.16/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/bragalund/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/172.4343.16/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/EksamensInnlevering.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/EksamensInnlevering.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EksamensInnlevering.dir/flags.make

CMakeFiles/EksamensInnlevering.dir/main.c.o: CMakeFiles/EksamensInnlevering.dir/flags.make
CMakeFiles/EksamensInnlevering.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/EksamensInnlevering.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/EksamensInnlevering.dir/main.c.o   -c /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/main.c

CMakeFiles/EksamensInnlevering.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/EksamensInnlevering.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/main.c > CMakeFiles/EksamensInnlevering.dir/main.c.i

CMakeFiles/EksamensInnlevering.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/EksamensInnlevering.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/main.c -o CMakeFiles/EksamensInnlevering.dir/main.c.s

CMakeFiles/EksamensInnlevering.dir/main.c.o.requires:

.PHONY : CMakeFiles/EksamensInnlevering.dir/main.c.o.requires

CMakeFiles/EksamensInnlevering.dir/main.c.o.provides: CMakeFiles/EksamensInnlevering.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/EksamensInnlevering.dir/build.make CMakeFiles/EksamensInnlevering.dir/main.c.o.provides.build
.PHONY : CMakeFiles/EksamensInnlevering.dir/main.c.o.provides

CMakeFiles/EksamensInnlevering.dir/main.c.o.provides.build: CMakeFiles/EksamensInnlevering.dir/main.c.o


# Object files for target EksamensInnlevering
EksamensInnlevering_OBJECTS = \
"CMakeFiles/EksamensInnlevering.dir/main.c.o"

# External object files for target EksamensInnlevering
EksamensInnlevering_EXTERNAL_OBJECTS =

EksamensInnlevering: CMakeFiles/EksamensInnlevering.dir/main.c.o
EksamensInnlevering: CMakeFiles/EksamensInnlevering.dir/build.make
EksamensInnlevering: CMakeFiles/EksamensInnlevering.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable EksamensInnlevering"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EksamensInnlevering.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EksamensInnlevering.dir/build: EksamensInnlevering

.PHONY : CMakeFiles/EksamensInnlevering.dir/build

CMakeFiles/EksamensInnlevering.dir/requires: CMakeFiles/EksamensInnlevering.dir/main.c.o.requires

.PHONY : CMakeFiles/EksamensInnlevering.dir/requires

CMakeFiles/EksamensInnlevering.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/EksamensInnlevering.dir/cmake_clean.cmake
.PHONY : CMakeFiles/EksamensInnlevering.dir/clean

CMakeFiles/EksamensInnlevering.dir/depend:
	cd /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/cmake-build-debug /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/cmake-build-debug /home/bragalund/Documents/C/Innleveringer/EksamensInnlevering/cmake-build-debug/CMakeFiles/EksamensInnlevering.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/EksamensInnlevering.dir/depend
