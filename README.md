# Overview

This is the repository for IEEE @ UH Manoa Spring 2017's
Pong-gramming Night workshop.

This is a Pong clone written in the C++ programming language with
a twist -- people can also program in their own implementations
to control the behavior of the paddles!

The goal of the workshop is to create pseudo-AI/game-AI to control
the paddles and crush your opponents in Pong!

Have fun. :)

# Directory Structure

- The `bin` directory contains the **bin**ary executables for the Pong
program.

- The `dep` directory holds any **dep**endency libraries/files required
to compile the entire project. This includes SDL, or the Simple DirectMedia
Layer library, as well as some of its auxillary extensions to use stuff
like images, text, and sound.

- The `src` directory contains the **source** files for the C++ code of
the program. Each team will make their own C++ file that implements a
certain function to control movement of a paddle in this folder.

- The `tests` directory contains some basic test cases for the project.

- Finally, the `Makefile` file is written for GNU Make or a similar program
  that can run Makefiles.
  - A **Makefile** is a file meant to be run by a program on a POSIX shell
    command line called `make`. It consists of a series of rules that
    run shell commands, usually to build your code.
    - POSIX is a generalized operating system standard. Linux and Mac OS X
      are mostly POSIX-compatible -- Windows is usually not.

# Getting Dependency Libraries

- The major dependency libraries are:
  - `SDL2`
  - `SDL2_ttf`
  - `SDL2_mixer`
  - `SDL2_image`

- You will have to download the **development libraries** for 
  these libraries from the SDL2 websites.
