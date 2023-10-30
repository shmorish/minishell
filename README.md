<h1 align="center">
	minishell
</h1>

<p align="center">
	<b><i>As beautiful as a shell</i></b><br>
</p>

---

## About the project

> _This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors._


## Usage

### Requirements

The function is written in C language and thus needs the **`cc` compiler** and some standard **C libraries** to run.

It's not included in the default environment of the Mac,<br>
You will need to install readline with the following command
```shell
brew install readline
```

### Instructions

**1. Compiling the program**

To compile, go to the program path and run:

```shell
make
```

**2. Executing the program**

To execute the program, run:

```C
./minishell
```

### Behaviors

This minishell now supports the following behaviors
#### Bulitins
- echo (including -n opiton)
- cd (with only a relative or absolute path)
- pwd (no options)
- export (no options)
- unset (no options)
- env (with no options or arguments)
- exit (no options)

#### Pipes and ridirect
- `|`  The output of each command in the pipeline is connected to the input of the next command via a pipe.
- `>` ridirect output
- `<` ridirect input
- `>>` ridirect output in append mode
- `<<` heredoc

#### Signals
- `ctrl-C` 
- `ctrl-D`
- `ctrl-\`

#### enviroment expands (including exit status)
