# general:
- error message to stderr.
- leak when exit.

---------------

# Path:
- `$PWD` would need to check if path is a directory.
  - giving a directory as command would give the same result, and the exit code isn't correctly set to 126. `/include`

- Can not run command from absolute path or semi absolute path: `/bin/ls`

- giving a file without permission give incorrect error message and code isnt set to 126. `./hello.txt` with hello.txt is a file without permission.

---------------

# Parsing:
- command `|` gives wrong error message instead of "syntax error near unexpected token `token'" and exit code not set to 2
- `<< echo oi` this doesnt recognise echo as LIMITER

---------------

# Redirection:
- Run these with valgrind. The command with redirection doesn't run and there is leak in some due to SIGSEGV
  - `cat <"./test_files/infile" | echo hi`
  - `cat <"./test_files/infile" | grep hello`
  - `cat <"./test_files/infile_big" | echo hi`
  - `echo hi >>./outfiles/outfile01 | echo bye`
  - and a few more of the same nature...

- `cat <<HERE <<DOC` not chaining properly. Doubt this will get tested though

-----------------

# Builtins and signals:
- conditional jump depends on uninitialised values in export_no_arg -> get_variable -> get_variable_helper
(pas possible a replique)

- $EMPTY not clear exit code. (plus complique que prevu, donc on ne probablement va pas faire)
