# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/david/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/171.4694.31/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/david/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/171.4694.31/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/Repos/MMN14

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/Repos/MMN14/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mmn14.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mmn14.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mmn14.dir/flags.make

CMakeFiles/mmn14.dir/src/main.c.o: CMakeFiles/mmn14.dir/flags.make
CMakeFiles/mmn14.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Repos/MMN14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mmn14.dir/src/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mmn14.dir/src/main.c.o   -c /home/david/Repos/MMN14/src/main.c

CMakeFiles/mmn14.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmn14.dir/src/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/david/Repos/MMN14/src/main.c > CMakeFiles/mmn14.dir/src/main.c.i

CMakeFiles/mmn14.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmn14.dir/src/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/david/Repos/MMN14/src/main.c -o CMakeFiles/mmn14.dir/src/main.c.s

CMakeFiles/mmn14.dir/src/main.c.o.requires:

.PHONY : CMakeFiles/mmn14.dir/src/main.c.o.requires

CMakeFiles/mmn14.dir/src/main.c.o.provides: CMakeFiles/mmn14.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/mmn14.dir/build.make CMakeFiles/mmn14.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/mmn14.dir/src/main.c.o.provides

CMakeFiles/mmn14.dir/src/main.c.o.provides.build: CMakeFiles/mmn14.dir/src/main.c.o


CMakeFiles/mmn14.dir/src/structures.c.o: CMakeFiles/mmn14.dir/flags.make
CMakeFiles/mmn14.dir/src/structures.c.o: ../src/structures.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Repos/MMN14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mmn14.dir/src/structures.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mmn14.dir/src/structures.c.o   -c /home/david/Repos/MMN14/src/structures.c

CMakeFiles/mmn14.dir/src/structures.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmn14.dir/src/structures.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/david/Repos/MMN14/src/structures.c > CMakeFiles/mmn14.dir/src/structures.c.i

CMakeFiles/mmn14.dir/src/structures.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmn14.dir/src/structures.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/david/Repos/MMN14/src/structures.c -o CMakeFiles/mmn14.dir/src/structures.c.s

CMakeFiles/mmn14.dir/src/structures.c.o.requires:

.PHONY : CMakeFiles/mmn14.dir/src/structures.c.o.requires

CMakeFiles/mmn14.dir/src/structures.c.o.provides: CMakeFiles/mmn14.dir/src/structures.c.o.requires
	$(MAKE) -f CMakeFiles/mmn14.dir/build.make CMakeFiles/mmn14.dir/src/structures.c.o.provides.build
.PHONY : CMakeFiles/mmn14.dir/src/structures.c.o.provides

CMakeFiles/mmn14.dir/src/structures.c.o.provides.build: CMakeFiles/mmn14.dir/src/structures.c.o


CMakeFiles/mmn14.dir/src/util_functions.c.o: CMakeFiles/mmn14.dir/flags.make
CMakeFiles/mmn14.dir/src/util_functions.c.o: ../src/util_functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Repos/MMN14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/mmn14.dir/src/util_functions.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mmn14.dir/src/util_functions.c.o   -c /home/david/Repos/MMN14/src/util_functions.c

CMakeFiles/mmn14.dir/src/util_functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmn14.dir/src/util_functions.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/david/Repos/MMN14/src/util_functions.c > CMakeFiles/mmn14.dir/src/util_functions.c.i

CMakeFiles/mmn14.dir/src/util_functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmn14.dir/src/util_functions.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/david/Repos/MMN14/src/util_functions.c -o CMakeFiles/mmn14.dir/src/util_functions.c.s

CMakeFiles/mmn14.dir/src/util_functions.c.o.requires:

.PHONY : CMakeFiles/mmn14.dir/src/util_functions.c.o.requires

CMakeFiles/mmn14.dir/src/util_functions.c.o.provides: CMakeFiles/mmn14.dir/src/util_functions.c.o.requires
	$(MAKE) -f CMakeFiles/mmn14.dir/build.make CMakeFiles/mmn14.dir/src/util_functions.c.o.provides.build
.PHONY : CMakeFiles/mmn14.dir/src/util_functions.c.o.provides

CMakeFiles/mmn14.dir/src/util_functions.c.o.provides.build: CMakeFiles/mmn14.dir/src/util_functions.c.o


CMakeFiles/mmn14.dir/src/directive_parser.c.o: CMakeFiles/mmn14.dir/flags.make
CMakeFiles/mmn14.dir/src/directive_parser.c.o: ../src/directive_parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Repos/MMN14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/mmn14.dir/src/directive_parser.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mmn14.dir/src/directive_parser.c.o   -c /home/david/Repos/MMN14/src/directive_parser.c

CMakeFiles/mmn14.dir/src/directive_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmn14.dir/src/directive_parser.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/david/Repos/MMN14/src/directive_parser.c > CMakeFiles/mmn14.dir/src/directive_parser.c.i

CMakeFiles/mmn14.dir/src/directive_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmn14.dir/src/directive_parser.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/david/Repos/MMN14/src/directive_parser.c -o CMakeFiles/mmn14.dir/src/directive_parser.c.s

CMakeFiles/mmn14.dir/src/directive_parser.c.o.requires:

.PHONY : CMakeFiles/mmn14.dir/src/directive_parser.c.o.requires

CMakeFiles/mmn14.dir/src/directive_parser.c.o.provides: CMakeFiles/mmn14.dir/src/directive_parser.c.o.requires
	$(MAKE) -f CMakeFiles/mmn14.dir/build.make CMakeFiles/mmn14.dir/src/directive_parser.c.o.provides.build
.PHONY : CMakeFiles/mmn14.dir/src/directive_parser.c.o.provides

CMakeFiles/mmn14.dir/src/directive_parser.c.o.provides.build: CMakeFiles/mmn14.dir/src/directive_parser.c.o


CMakeFiles/mmn14.dir/src/general_parsing.c.o: CMakeFiles/mmn14.dir/flags.make
CMakeFiles/mmn14.dir/src/general_parsing.c.o: ../src/general_parsing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Repos/MMN14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/mmn14.dir/src/general_parsing.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mmn14.dir/src/general_parsing.c.o   -c /home/david/Repos/MMN14/src/general_parsing.c

CMakeFiles/mmn14.dir/src/general_parsing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmn14.dir/src/general_parsing.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/david/Repos/MMN14/src/general_parsing.c > CMakeFiles/mmn14.dir/src/general_parsing.c.i

CMakeFiles/mmn14.dir/src/general_parsing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmn14.dir/src/general_parsing.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/david/Repos/MMN14/src/general_parsing.c -o CMakeFiles/mmn14.dir/src/general_parsing.c.s

CMakeFiles/mmn14.dir/src/general_parsing.c.o.requires:

.PHONY : CMakeFiles/mmn14.dir/src/general_parsing.c.o.requires

CMakeFiles/mmn14.dir/src/general_parsing.c.o.provides: CMakeFiles/mmn14.dir/src/general_parsing.c.o.requires
	$(MAKE) -f CMakeFiles/mmn14.dir/build.make CMakeFiles/mmn14.dir/src/general_parsing.c.o.provides.build
.PHONY : CMakeFiles/mmn14.dir/src/general_parsing.c.o.provides

CMakeFiles/mmn14.dir/src/general_parsing.c.o.provides.build: CMakeFiles/mmn14.dir/src/general_parsing.c.o


CMakeFiles/mmn14.dir/src/string_parser.c.o: CMakeFiles/mmn14.dir/flags.make
CMakeFiles/mmn14.dir/src/string_parser.c.o: ../src/string_parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Repos/MMN14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/mmn14.dir/src/string_parser.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mmn14.dir/src/string_parser.c.o   -c /home/david/Repos/MMN14/src/string_parser.c

CMakeFiles/mmn14.dir/src/string_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmn14.dir/src/string_parser.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/david/Repos/MMN14/src/string_parser.c > CMakeFiles/mmn14.dir/src/string_parser.c.i

CMakeFiles/mmn14.dir/src/string_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmn14.dir/src/string_parser.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/david/Repos/MMN14/src/string_parser.c -o CMakeFiles/mmn14.dir/src/string_parser.c.s

CMakeFiles/mmn14.dir/src/string_parser.c.o.requires:

.PHONY : CMakeFiles/mmn14.dir/src/string_parser.c.o.requires

CMakeFiles/mmn14.dir/src/string_parser.c.o.provides: CMakeFiles/mmn14.dir/src/string_parser.c.o.requires
	$(MAKE) -f CMakeFiles/mmn14.dir/build.make CMakeFiles/mmn14.dir/src/string_parser.c.o.provides.build
.PHONY : CMakeFiles/mmn14.dir/src/string_parser.c.o.provides

CMakeFiles/mmn14.dir/src/string_parser.c.o.provides.build: CMakeFiles/mmn14.dir/src/string_parser.c.o


CMakeFiles/mmn14.dir/src/individual_directives.c.o: CMakeFiles/mmn14.dir/flags.make
CMakeFiles/mmn14.dir/src/individual_directives.c.o: ../src/individual_directives.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Repos/MMN14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/mmn14.dir/src/individual_directives.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mmn14.dir/src/individual_directives.c.o   -c /home/david/Repos/MMN14/src/individual_directives.c

CMakeFiles/mmn14.dir/src/individual_directives.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mmn14.dir/src/individual_directives.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/david/Repos/MMN14/src/individual_directives.c > CMakeFiles/mmn14.dir/src/individual_directives.c.i

CMakeFiles/mmn14.dir/src/individual_directives.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mmn14.dir/src/individual_directives.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/david/Repos/MMN14/src/individual_directives.c -o CMakeFiles/mmn14.dir/src/individual_directives.c.s

CMakeFiles/mmn14.dir/src/individual_directives.c.o.requires:

.PHONY : CMakeFiles/mmn14.dir/src/individual_directives.c.o.requires

CMakeFiles/mmn14.dir/src/individual_directives.c.o.provides: CMakeFiles/mmn14.dir/src/individual_directives.c.o.requires
	$(MAKE) -f CMakeFiles/mmn14.dir/build.make CMakeFiles/mmn14.dir/src/individual_directives.c.o.provides.build
.PHONY : CMakeFiles/mmn14.dir/src/individual_directives.c.o.provides

CMakeFiles/mmn14.dir/src/individual_directives.c.o.provides.build: CMakeFiles/mmn14.dir/src/individual_directives.c.o


# Object files for target mmn14
mmn14_OBJECTS = \
"CMakeFiles/mmn14.dir/src/main.c.o" \
"CMakeFiles/mmn14.dir/src/structures.c.o" \
"CMakeFiles/mmn14.dir/src/util_functions.c.o" \
"CMakeFiles/mmn14.dir/src/directive_parser.c.o" \
"CMakeFiles/mmn14.dir/src/general_parsing.c.o" \
"CMakeFiles/mmn14.dir/src/string_parser.c.o" \
"CMakeFiles/mmn14.dir/src/individual_directives.c.o"

# External object files for target mmn14
mmn14_EXTERNAL_OBJECTS =

mmn14: CMakeFiles/mmn14.dir/src/main.c.o
mmn14: CMakeFiles/mmn14.dir/src/structures.c.o
mmn14: CMakeFiles/mmn14.dir/src/util_functions.c.o
mmn14: CMakeFiles/mmn14.dir/src/directive_parser.c.o
mmn14: CMakeFiles/mmn14.dir/src/general_parsing.c.o
mmn14: CMakeFiles/mmn14.dir/src/string_parser.c.o
mmn14: CMakeFiles/mmn14.dir/src/individual_directives.c.o
mmn14: CMakeFiles/mmn14.dir/build.make
mmn14: CMakeFiles/mmn14.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/david/Repos/MMN14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable mmn14"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mmn14.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mmn14.dir/build: mmn14

.PHONY : CMakeFiles/mmn14.dir/build

CMakeFiles/mmn14.dir/requires: CMakeFiles/mmn14.dir/src/main.c.o.requires
CMakeFiles/mmn14.dir/requires: CMakeFiles/mmn14.dir/src/structures.c.o.requires
CMakeFiles/mmn14.dir/requires: CMakeFiles/mmn14.dir/src/util_functions.c.o.requires
CMakeFiles/mmn14.dir/requires: CMakeFiles/mmn14.dir/src/directive_parser.c.o.requires
CMakeFiles/mmn14.dir/requires: CMakeFiles/mmn14.dir/src/general_parsing.c.o.requires
CMakeFiles/mmn14.dir/requires: CMakeFiles/mmn14.dir/src/string_parser.c.o.requires
CMakeFiles/mmn14.dir/requires: CMakeFiles/mmn14.dir/src/individual_directives.c.o.requires

.PHONY : CMakeFiles/mmn14.dir/requires

CMakeFiles/mmn14.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mmn14.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mmn14.dir/clean

CMakeFiles/mmn14.dir/depend:
	cd /home/david/Repos/MMN14/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Repos/MMN14 /home/david/Repos/MMN14 /home/david/Repos/MMN14/cmake-build-debug /home/david/Repos/MMN14/cmake-build-debug /home/david/Repos/MMN14/cmake-build-debug/CMakeFiles/mmn14.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mmn14.dir/depend
