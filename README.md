# MiniShell

## 1. Project Description

MiniShell is a simple Unix-like command shell developed in C.

The project aims to understand how a shell reads user commands, processes them, creates processes, and executes programs in a Linux environment.

## 2. Problem Statement

When a user enters a command in a terminal, the shell performs several operations such as reading the input, parsing the command, creating processes, executing programs, handling input/output, and connecting commands using pipes.

MiniShell implements these basic operations from scratch in C to understand how a command shell works internally.

## 3. Goals

- Understand the basic working of a Unix shell.
- Learn how commands are read and parsed.
- Understand process creation and program execution.
- Learn how Linux system calls are used.
- Understand file descriptors and input/output redirection.
- Understand inter-process communication using pipes.
- Learn basic signal handling.
- Practice system-level programming in C.

## 4. Specifications

MiniShell will provide:

- Interactive command prompt
- Command parsing
- `cd` command
- `pwd` command
- `echo` command
- `cat` command
- `exit` command
- External command execution
- Basic error handling
- Input redirection using `<`
- Output redirection using `>`
- Input and output redirection together
- Pipe `|` between commands
- Basic signal handling

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
Check Redirection / Pipe
    ↓
Execute
    ↓
Display Output
    ↓
Show Prompt Again