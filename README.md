# 42sh

Disclaimer: this is first-year student code, thus it is *far* from perfect.

## Features:
* Regular shell features (commands, &&, ||, redirections, pipes, ...)
* Input can be read from stdin or a file
* Input is translated into an AST, then executed in a LL-like fashion
* Termcaps display
* Completion for commands and files (Tab to show, Enter to accept, q to quit)
* Basic alias support
* Configuration file (see .42shrc)
* Classic builtins (cd, echo, env, exit, bang, ...)
* History accessible with the arrow keys
* Customizable prompt (see .42shrc for an example)
* Basic globbing support
* Double quotes support (but they actually act as simple quotes, lol)
* Basic real-time syntax highlighting for commands (binary, builtin, or not found) and quotes
* Tiny man page
* Tiny moulinette (compares the shell with tcsh)