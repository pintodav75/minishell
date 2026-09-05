# minishell

A small POSIX-style shell in C — a subset of `bash`, written from a blank file.
**Two-person project.**

**Language:** C + GNU readline (`-Wall -Wextra -Werror`) · **Context:** 42 School

## Run

```bash
make
./minishell
```

## Features

- **Prompt & history** via `readline` (`add_history`).
- **Lexer → parser → AST.** The input is tokenised, tokens are grouped into
  command nodes and redirection nodes, and the whole line becomes a small syntax
  tree that the executor walks. Syntax errors (unclosed quotes, misplaced `|`,
  stray `<`/`>`) are reported before anything runs.
- **Quoting.** Single quotes are literal; double quotes allow `$` expansion but
  suppress word splitting.
- **Expansion.** Environment variables, `$?` (last exit status), and `$$`.
- **Pipelines** of arbitrary length, each stage `fork`ed and wired with `pipe`.
- **Redirections:** `<`, `>`, `>>`, and here-docs `<<` (with expansion in the
  here-doc body unless the delimiter is quoted).
- **Builtins**, implemented by hand: `echo -n`, `cd` (with `OLDPWD`/`PWD`),
  `pwd`, `export`, `unset`, `env`, `exit`.
- **Signals:** `Ctrl-C`, `Ctrl-D` and `Ctrl-\` behave as in bash, both at the
  prompt and while a command runs.

## Structure

```
src/parsing/lexer     tokeniser
src/parsing/parser     tokens → AST
src/exe               executor: pipelines, redirections, here-docs, builtins
src/builtin           builtin implementations
src/signals           interactive signal handling
src/ft_free           teardown / leak-free exit paths
```

## Notes

- Readline's own allocations aside, the shell is leak-free on every exit path.
- Exit codes mirror bash, including `127` (command not found) and `126`
  (not executable).

