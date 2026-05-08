High-Level Structure of the Solution:

This project implements a minimal shell named mysh that reads user input, parses it, and executes commands in a REPL loop. The shell handles built-in commands (mypwd, mycd, exit) directly within the shell process and external alias commands (myls → ls, mygrep → grep) via child processes using fork() and execvp(). The shell ignores leading/trailing whitespace, collapses repeated spaces/tabs, tokenizes input using whitespace, and prints appropriate error messages for unknown commands or execution failures.

The shell loop uses the skeleton structure exactly as provided. Each input line is read character by character and accumulated in a buffer. When a newline is encountered, the input is cleaned, tokenized, and dispatched to the appropriate command handler. External commands run in child processes while the shell waits for their completion using wait(). The shell exits cleanly on exit or EOF (Ctrl-D).



Feature Status:

REPL loop & prompt correctness (mysh# with trailing space) — Fully implemented

Parsing & tokenization (ignores extra whitespace, handles empty lines) — Fully implemented

Built-in mypwd — Fully implemented

Built-in mycd <path> (valid, missing, invalid path handling) — Fully implemented

Built-in exit — Fully implemented

External alias myls [args...] — Fully implemented

External alias mygrep [args...] — Fully implemented

Unknown command messages — Fully implemented

Buffer overflow prevention — Implemented



How the Solution Was Tested
Commands Tested:


Built-ins:

mypwd → prints current directory

mycd /valid/path → changes directory

mycd → prints usage: mycd <path>

mycd /invalid/path → prints No such directory

exit → exits shell

External aliases:

myls → lists directory contents

myls -a → lists all files including hidden

mygrep pattern filename → searches file for pattern


Unknown commands:

foo → prints Command not found

Edge cases:

Empty input → prints prompt again

Leading/trailing spaces → correctly ignored

Multiple spaces/tabs → collapsed into single separator

Input longer than 99 characters → does not overflow buffer

EOF (Ctrl-D) → exits shell cleanly
