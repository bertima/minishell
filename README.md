_This project has been created as part of the 42 curriculum by Bertrmar._

# MINISHELL &nbsp; ![Bash](https://img.shields.io/badge/Bash-4EAA25?style=for-the-badge&logo=gnubash&logoColor=white)

## Table of Content

1. [Description](#descitpion)
2. [Instruction](#instructions)
	- [Prerequisites](#prerequisites)
	- [Run Project](#run-project)
3. [Features](#features)
4. [Author](#author)

## Descitpion

Bash (an acronym for Bourne-Again SHell) is an interactive command interpreter and scripting language that serves as the default shell for most Linux distributions and macOS systems.

This project aims to replicate the behavior of the standard bash shell based on this document:  
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/

## Instructions

### Prerequisites
- Disrtibution Linux / MacOS (POSIX-compliant systems).
- Compiler C (`cc` ou `gcc`)
- Make
- Library GNU Readline (`libreadline-dev`)

Clone the project to your computer and navigate to the folder that was created:

```
git clone git@github.com:bertima/minishell.git minishell && cd minishell
```
You are now in the project titled minshell.

### Run Project


This project work with makefile, for launch your prompt use;

```
make && ./minishell
```
## Features

Interactive prompt with history support (via Readline).

- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\).

- Full parsing: lexical and syntactic analysis of commands, arguments, and chevrons.

- Redirections: <, >, >>, and support for << (here-doc).

- Pipes: chaining multiple commands with |.

- Expansions: support for environment variables ($VAR) and exit codes ($?).

Built-in commands:

- echo (with the -n option)

- cd (relative and absolute paths, support for . and ..)

- pwd

- export

- unset

- env

- exit

## Author

- **Bertrand Martin** ([github](https://github.com/bertima))
