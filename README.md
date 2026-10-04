# MiniShell

A simple Unix-like command shell built from scratch in C.

## Project Description

MiniShell is a small command-line shell developed in C to understand how a shell works internally and how Linux processes and system calls are used to execute commands.

## Problem Statement

When users run commands in a Linux terminal, the shell reads user input, interprets commands, and executes programs.

The goal of MiniShell is to build a simplified shell from scratch and understand the basic mechanisms involved in command execution.

## Goals

- Understand how a shell works internally.
- Learn how user input is read and parsed.
- Understand Linux process creation and program execution.
- Practice C programming through a system-level project.
- Understand basic input/output redirection.
- Build a small and modular shell.

## Planned Features

- Interactive command prompt
- Command parsing
- Built-in commands such as `cd`, `pwd`, `echo`, and `cat`
- Execute external Linux commands
- Basic error handling
- Output redirection using `>`

## Project Structure

```text
MiniShell/
├── src/
│   └── main.c
├── include/
├── tests/
├── .gitignore
├── Makefile
└── README.md