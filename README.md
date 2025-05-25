Bugs:
- Critical: `export a=b` , a=b isnt marked as TK_Assign after treated in parser, so export assign is broken. The bug is very likely from
  `int handle_assign(t_pctx *ctx, t_node **nodeptr)` in handlers.c in parsers
- Il n'y a pas de rule dans makefile pour compile libft.
- exit code in executor.
- leak when exit because tree isnt free.

--------------
- Fixed: ft_lstadd_back_env() now correctly set the ->next to NULL.
- Fixed: unset segfault when unset first env variable.
- Fixed: unset builtin is included in executor.h and in builtin lookup function.
- Fixed: echo segfault when running with no environnement.
- Fixed: builtin lookup not working proprely. It skips first built-in and last built-in.
- Fixed: cd .. segfault when running with no environnement.
- Fixed: passing t_env *env to exec_bin and exec_cmd instead of t_env **env.

--------------

# Nguyen todo:
- exit buildin:
    - Cleanup (ast tree and such) before exit.
- Signal:
    - Cleanup child process in SIGQUIT (CTRL \).
    - In child processes:
          - insert when fork child
	```
 	if (pid == 0)
 	{
		if (signal_handler())
			return (1);
  		execute_child_process();
  		...
 	}
	```
- Assign:
    - If a variable that exist in env is assigned, it will replace the value in env.
    - If a variable that doesn't exist in env, then a linked list of variable is created to hold this new key value pair.


### Changelog:

----------------
25 May: Nguyen
- Fix bugs.
  
----------------
12 May: Nguyen
- Signal now work correctly in interactive mode.
- Now handle exit
    - exit with no argument: exit with exit code stored in env.
    - exit with number: exit with entered number. If number > 256, then code % 256. Code is unsigned int.
    - exit with non numeric argument: print error and exit with code 255.
    - exit with more than 2 arguments: print error, not exit and return/set code 1.
    - print "exit\n" in interactive mode.
- All relevent exit codes are now set with set_get_code().
- Code is new restructured to separate libft and to indicate which files to copy.

----------------
04 May: Nguyen
- Now initiate variable ? during shell launch
    - key is ?
    - value is the exit code in string.
- Now handle $? expansion.
- Function set_get_code(int code, t_env **env) is now used to manage exit code
    - If code -1 is passed to the function, the exit code stored in variable ? is returned.
    - If any code other than -1 is passed to the function, the variable ? is updated with the code, and this code is then returned.

----------------
02 May: Nguyen
- Now handle cd
    - cd path
    - cd -
    - cd
    - cd ~ (Note: This is not tested)
- Now initiate SHLVL and PWD when shell start in case of no environnement.
- Now SHLVL is correctly incremented everytime a new shell is open.

----------------
30 April: Nguyen
- Changed structure of t_env.
- Now export without argument is handled and output is sorted.
- Now handle unset with multiple arguments.

NOTE: The main to test is bugged.

----------------
29 April: Nguyen
- Now handle export:
    - eg: export USER=test
    - eg: export USER
    - eg: export nonExistedVariable

NOTE: The main to test is bugged.

----------------
25 April: Nguyen
- Now handle bonus "'$USER'" and '"$USER"'
- Remove TK_Usd token
- Bugs fix

----------------
24 April: Nguyen
- Now handle $ expansion
    - NOTE: $? not handled and will segfault.
- Move all file under single lexer.h
- Bugs fix

----------------
23 April: Nguyen
- Changing the structure of char **envp to a linked list
    - to pass the envp to execve(), use 
        - char	**env_to_envp(t_env **env);
        - void	free_envp(char **envp);

----------------
20 April: Nguyen
- Start of Builtins.
- Now handle env.
- Now handle pwd.
- Now partially handle echo.
    - Handle echo.
    - Handle echo -n.
    - Variable expansion $ isn't handled yet, waiting for Assignation component.
    - Quotes not trimmed yet. 

----------------
18 April: Nguyen
- Start of Signal.
- Now handle CTRL-C in main, which mean it correctly starts a new prompt on a new line.
    - CTRL-C behaves differently in child process (clean and kill the process). This will be handled later.
- CTRL-\ is currently used to exit the minishell.
    - By default CTRL-\ does nothing in main.
    - CTRL-\ behaves differently in child process (core dumped). This will be handled later.
- CTRL-D apparently is not a signal, to be studied further.

----------------
14 April: Nguyen
- Start of executor.
- The executor doesn't compile nor working. It is served as a complementary guideline to the [minishell flow](https://www.figma.com/board/Jq8jCcA387ejD9taclT17H/Minishell-flow?node-id=0-1&t=2iSGymJoeilHbcG0-1).
  The executor will be reworked later.
- The logic behind the executor is recursively apply the executor function to nodes.
    - The base cases are NT_Cmd and NT_Candidate (Assume to be null?).
    - The variable " i " serve as exit code. It should be initated outside the executor and is passed around using pointer.
- No error handling for now.

----------------
10 April: Nguyen
- input.h: Minor modifications to align with the parser and add TK_Number.
    - IMPORTANT: TK_Number format is a String. So need to run atoi on it during execution.
- Fixed bug where $ alone is a token, it is now a string.
- Fixed bug where redirection tokens not created if there is no space before or after redirection.
    - eg: echo hello>>out.txt -> TK_String TK_String TK_Append TK_tring.
- Token is now correctly created to handle file descriptor precede redirection.
    - eg: 213>out.txt -> TK_Number TK_Out TK_String.
    - eg: 87124<< text -> TK_Number TK_HereDoc TK_String.
    - eg: echo 3242 << text -> TK_String TK_String TK_HereDoc TK_String.
- Token $ now is only created of $ is not followed by whitespace, \0, <, > or |. 
    - "$ ?", $ is a string, ? is a string.
    - "$|", $ is a string, | is a pipe.
    - "$?", $ is a $ token, ? is a string.
- Norminette est bonne.

----------------
07 April: Nguyen
- input.h: Created TK_Assign type to handle Assignment. eg: VAR=test or _VAR=test.
- Lexer now creates token from Assignement string. A token would be of value "VAR=test" and type TK_Assign.
- Token $ now is only created of $ is not followed by whitespace. 
    - "$ ?", $ is a string, ? is a string.
    - "$?", $ is a $ token, ? is a string.
- Working history is now available.
- Bugs fix.

// Wildcard not handle.
  (Probably better to handle it during the execution by looping through string to check for $ and *).

----------------
06 April: Nguyen
- input.h: Created more type of token.
- Lexer now creates token from single characters: >, <, |, $.
    - $ is subject to change due to uncertainty of its application outside of quote.
- Lexer now creates token from double characters: >>, <<, ||, &&.
- Lexer now creates tokens from strings: double quote "", single quote '', no quote.
    - Doesn't handle any special characters because backslash \ is not a requirement.
      This mean string starts at the first quote and end at the second quote of the same type.
    - Doesn't handle unclosed quotes because it is not a requirement.
- Lexer returns a linked list of tokens.

// Lexer doesn't handle variable assignment = and wildcard * for now.

----------------
04 April: Nguyen
- input.h: change token structure to make a linked list of token.
- add various files to Nguyen directory.
