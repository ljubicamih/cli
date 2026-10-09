# cli

A small Unix-style command-line interpreter written in C++20. It reads commands from the terminal, parses them with a hand-written state-machine parser, and executes them through an extensible command architecture. It supports piping (`|`), input and output redirection (`<`, `>`, `>>`) and batch script execution.

## Features

- **Pipes:** chain commands, e.g. `echo "hello world" | tr -"o" "0" | wc -w`
- **I/O redirection:** read from a file, write (`>`) or append (`>>`) to a file
- **Batch execution:** run a file of commands with `batch`
- **Custom prompt:** change the prompt at runtime with `prompt`
- **Error handling:** lexical and syntax errors are reported with the position of the problem instead of crashing the interpreter


Commands that read data take it from, in order: a file or quoted-string argument, the previous command in a pipe, or standard input.

## Examples

```
$ echo "hello world" | wc -w
2
$ echo "hello world" | tr -"o" "0"
hell0 w0rld
$ head -n2 notes.txt
first line
second line
$ echo "first" > log.txt
$ echo "second" >> log.txt
$ batch commands.txt
$ prompt "cli>"
cli> last
```

Rules for pipes and redirection: only the first command of a pipe may take an input argument, and only the last may redirect its output.

## Architecture

The project is organised around the **Command pattern**:

- `Command` is an abstract base class with a virtual `execute()`. Each command (`Echo`, `Date`, `Head`, ...) derives from it and works on an input and an output stream it is given, so the same code works for the terminal, files and pipes.
- `CommandRegistry` is a singleton factory. `registerAllCommands()` registers every command by name together with a `create` function, so adding a command means writing one class and one registration line.
- `CommandContext` carries everything a command needs (name, argument, option, streams, a pointer to the interpreter), which keeps commands independent from the parser.
- `Parser` is a state machine that turns one line into a command name, option, arguments and redirection target.
- `Interpreter` splits a line on `|`, wires streams between stages, handles redirection, and runs the read-parse-execute loop. Commands that change the interpreter itself (`prompt`, `exit`, `batch`, `last`) call back into it.
- Commands are created and owned through `std::unique_ptr`.

## Project structure

```
cli/
├── CMakeLists.txt
├── main.cpp          entry point
├── h/                all header files
└── src/              all source files except main.cpp
```


**Platform note:** `time` currently uses `localtime_s`, which is available on Windows (MSVC and MinGW). On Linux or macOS replace it with `localtime_r(&currentTime, &localTime)` in `src/Time.cpp`.
