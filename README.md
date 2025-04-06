## Changelog:

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

- Lexer doesn't handle variable assignment = and wildcard * for now


04 April: Nguyen
- input.h: change token structure to make a linked list of token.
- add various files to Nguyen directory.
