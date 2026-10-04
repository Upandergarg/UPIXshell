# MiniShell

## 1. Project Description

MiniShell is a simple Unix-like command shell developed in C.

The project aims to understand how a shell reads user commands, processes them, and executes programs in a Linux environment.

## 2. Problem Statement

When a user enters a command in a terminal, the shell performs several operations such as reading the input, parsing the command, creating processes, executing programs, and handling input/output.

MiniShell implements these basic operations from scratch in C to understand how a command shell works internally.

## 3. Goals

- Understand the basic working of a Unix shell.
- Learn how commands are read and parsed.
- Understand process creation and program execution.
- Learn how Linux system calls are used.
- Understand file descriptors and output redirection.
- Practice system-level programming in C.

## 4. Specifications

MiniShell will provide:

- Interactive command prompt
- Command parsing
- `cd` command
- `pwd` command
- `echo` command
- `cat` command
- External command execution
- Basic error handling
- Output redirection using `>`

## 5. Design

The shell follows this basic flow:

```text
User Input
    ↓
Read Command
    ↓
Parse Command
    ↓
Check Command
    ↓
Execute
    ↓
Display Output