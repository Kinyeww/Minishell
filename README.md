*This project has been created as part of the 42 curriculum by ckin-yew, syee.*

# Minishell

## Description

Minishell is a 42 project that recreates a simple Unix shell.

The goal of this project is to understand how a shell works internally.
It reads user input, separates the input into tokens, parses the command structure, handles quotes, expands environment variables, processes redirections and pipes, then executes the command.

This project also teaches important system programming concepts such as process creation, file descriptors, signals, environment variables, and exit status handling.

Minishell does not aim to fully recreate Bash.
It only implements the required features from the 42 Minishell subject.

---

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will create the executable:

```bash
./minishell
```

### Execution

To run Minishell:

```bash
./minishell
```

Example:

```bash
Minishell$ echo hello
hello

Minishell$ pwd
/home/user/minishell

Minishell$ echo $USER
username
```

### Cleaning

To remove object files:

```bash
make clean
```

To remove object files and the executable:

```bash
make fclean
```

To rebuild the project:

```bash
make re
```

---

## Features

Minishell supports:

* Displaying a prompt and waiting for user input
* Command history using `readline`
* Executing commands using absolute path, relative path, or `PATH`
* Environment variable expansion, including `$?`
* Single quotes and double quotes
* Pipes using `|`
* Redirections:

  * `<` input redirection
  * `>` output redirection
  * `>>` append redirection
  * `<<` heredoc
* Signal handling:

  * `Ctrl + C`
  * `Ctrl + D`
  * `Ctrl + \`
* Built-in commands:

  * `echo`
  * `cd`
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`

---

## Usage Examples

### Pipe

```bash
ls | grep minishell
```

### Output Redirection

```bash
echo hello > file.txt
```

### Append Redirection

```bash
echo world >> file.txt
```

### Input Redirection

```bash
cat < file.txt
```

### Heredoc

```bash
cat << EOF
hello
world
EOF
```

### Environment Variable Expansion

```bash
echo $HOME
echo $?
```

---

## Project Flow

The general flow of Minishell is:

1. Read user input with `readline`
2. Tokenise the input
3. Parse tokens into command structures
4. Process heredoc if needed
5. Expand variables
6. Handle redirections and pipes
7. Execute built-ins or external commands
8. Update the exit status
9. Free allocated memory before reading the next input

---

## Important Concepts Learned

This project helped us understand:

* How a shell reads and executes commands
* How to create processes using `fork`
* How to execute programs using `execve`
* How to use `pipe`, `dup2`, `open`, and `close`
* How parent and child processes behave
* How to manage environment variables
* How to handle signals in interactive and execution modes
* How to manage memory in a long-running program
* How to parse user input while respecting quotes and operators

---

## Resources

Classic references used for this project:

* 42 Minishell subject PDF
* Bash manual: https://www.gnu.org/software/bash/manual/
* GNU Readline documentation: https://tiswww.case.edu/php/chet/readline/rltop.html
* pipe() and fork() : https://www.geeksforgeeks.org/c/c-program-demonstrate-fork-and-pipe/
* execve : https://www.youtube.com/watch?v=Wtd-8OiZOjk
* overall minishell breakdown : https://portfolio.beddinao.me/projects/mini-shell
* exit codes : https://www.redhat.com/en/blog/exit-codes-demystified
* Linux manual pages:

  * `man bash`
  * `man fork`
  * `man execve`
  * `man pipe`
  * `man dup2`
  * `man open`
  * `man close`
  * `man waitpid`
  * `man signal`
  * `man readline`

### Use of AI

AI was used as a learning and support tool during this project.

It was used to:

* Explain shell concepts in simpler words
* Understand how parsing, heredoc, redirection, pipes, signals, and exit status work
* Review code logic and suggest safer structure
* Help provide guidance in debigging code
* Help draft comments, explanations, and this README file

AI was not used to replace understanding of the project.
The final code was reviewed, tested, and adapted by the project members.
