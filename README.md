# Minishell

Minishell is a 42 project that implements a compact interactive Unix shell. It
parses command lines, expands environment variables, executes programs and
built-ins, connects pipelines, applies redirections, and handles interactive
signals while maintaining its own environment state.

## Features

- Interactive prompt powered by GNU Readline
- Command history
- Executable lookup through `PATH`
- Single and double quotes
- Environment expansion with `$VAR` and `$?`
- Pipelines with `|`
- Input redirection with `<`
- Output redirection with `>`
- Append redirection with `>>`
- Here-documents with `<<`
- `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` handling
- Exit-status propagation

Implemented built-ins:

| Built-in | Behavior |
| --- | --- |
| `echo` | Prints arguments and supports `-n` |
| `cd` | Changes directory, including `~` and `-` handling |
| `pwd` | Prints the current directory |
| `export` | Adds or updates environment variables |
| `unset` | Removes an environment variable |
| `env` | Prints the environment |
| `exit` | Exits with an optional numeric status |

Shell features outside the project scope, such as `&&`, `||`, wildcards, and
job control, are not implemented.

## Requirements

- A Unix-like operating system
- `cc`
- `make`
- GNU Readline headers and library

On Debian or Ubuntu, Readline can be installed with:

```sh
sudo apt install libreadline-dev
```

## Build

```sh
make
```

Available targets:

```sh
make          # build minishell and its local libraries
make clean    # remove object files
make fclean   # remove object files, libraries, and minishell
make re       # rebuild everything
make runb     # run under Valgrind
```

The project is compiled with `-Wall -Wextra -Werror` and linked with
`-lreadline`.

## Usage

Start the shell without arguments:

```sh
./minishell
```

Example session:

```text
minishell$ echo "$USER"
pechyvo
minishell$ printf "one\ntwo\nthree\n" | grep tw | wc -l
1
minishell$ echo hello > output.txt
minishell$ cat < output.txt
hello
minishell$ echo $?
0
minishell$ exit
exit
```

The shell does not accept command-line arguments.

## Architecture

The implementation is divided into three main stages:

1. **Parsing** validates syntax, tokenizes input, handles quotes and variable
   expansion, and builds a linked list of commands.
2. **Execution** resolves executables and built-ins, creates pipes and child
   processes, applies redirections, and collects exit statuses.
3. **Cleanup** releases per-command allocations through the local destructor
   utility before returning to the prompt.

## Project structure

```text
.
├── incl/
│   └── minishell.h          # shared structures and declarations
├── srcs/
│   ├── parse/               # tokenization, quoting, expansion, commands
│   ├── exec/                # execution, built-ins, pipes, redirections
│   ├── utils/               # environment, errors, strings, and cleanup
│   └── main.c               # prompt loop and signal setup
├── libft/                   # bundled Libft
├── ft_destructor/           # allocation-tracking support library
├── 42_pipex/                # bundled support code and ft_printf
├── subject/
│   └── en.subject_minishell.pdf
└── Makefile
```

## Project subject

The complete assignment is available in
[subject/en.subject_minishell.pdf](./subject/en.subject_minishell.pdf).
