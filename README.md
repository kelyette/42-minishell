Bugs:
- exit code.
- error message to stderr.
- leak when exit.
- $PWD would need to check if path is a directory.

Run these with valgrind. The command with redirection doesn't run and there is leak in some due to SIGSEGV
- cat <"./test_files/infile" | echo hi
- cat <"./test_files/infile" | grep hello
- cat <"./test_files/infile_big" | echo hi
- echo hi >>./outfiles/outfile01 | echo bye

Can not run command from absolute path or semi absolute path
