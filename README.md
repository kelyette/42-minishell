## Changelog:

14 April: Nguyen

- Start of executor
- The executor doesn't compile nor working. It is served as a complementary guideline to the [minishell flow](https://www.figma.com/board/Jq8jCcA387ejD9taclT17H/Minishell-flow?node-id=0-1&t=2iSGymJoeilHbcG0-1).
  The executor will be reworked later.
- The logic behind the executor is recursively apply the executor function to nodes.
    - The base cases are NT_Cmd and NT_Candidate (Assume to be null?)
    - The variable " i " serve as exit code. It should be initated outside the executor and is passed around using pointer.

----------------
10 April: Nguyen
- input.h: Minor modifications to align with the parser and add TK_Number
    - IMPORTANT: TK_Number format is a String. So need to run atoi on it during execution
- Fixed bug where $ alone is a token, it is now a string
- Fixed bug where redirection tokens not created if there is no space before or after redirection
    - eg: echo hello>>out.txt -> TK_String TK_String TK_Append TK_tring
- Token is now correctly created to handle file descriptor precede redirection
    - eg: 213>out.txt -> TK_Number TK_Out TK_String
    - eg: 87124<< text -> TK_Number TK_HereDoc TK_String
    - eg: echo 3242 << text -> TK_String TK_String TK_HereDoc TK_String
- Token $ now is only created of $ is not followed by whitespace, \0, <, > or |. 
    - "$ ?", $ is a string, ? is a string
    - "$|", $ is a string, | is a pipe
    - "$?", $ is a $ token, ? is a string
- Norminette est bonne

----------------
07 April: Nguyen
- input.h: Created TK_Assign type to handle Assignment. eg: VAR=test or _VAR=test;
- Lexer now creates token from Assignement string. A token would be of value "VAR=test" and type TK_Assign
- Token $ now is only created of $ is not followed by whitespace. 
    - "$ ?", $ is a string, ? is a string
    - "$?", $ is a $ token, ? is a string
- Working history is now available
- Bugs fix

// Wildcard not handle.
  (Probably better to handle it during the execution by looping through string to check for $ and *)

----------------
06 April: Nguyen
- input.h: Created more type of token
- Lexer now creates token from single characters: >, <, |, $ 
    - $ is subject to change due to uncertainty of its application outside of quote
- Lexer now creates token from double characters: >>, <<, ||, &&
- Lexer now creates tokens from strings: double quote "", single quote '', no quote
    - Doesn't handle any special characters because backslash \ is not a requirement.
      This mean string starts at the first quote and end at the second quote of the same type.
    - Doesn't handle unclosed quotes because it is not a requirement
- Lexer returns a linked list of tokens

// Lexer doesn't handle variable assignment = and wildcard * for now

----------------
04 April: Nguyen
- input.h: change token structure to make a linked list of token.
- add various files to Nguyen directory.
