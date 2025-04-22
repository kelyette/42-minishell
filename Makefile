CC           := gcc # TODO
RM           := rm -rf

CCFLAGS      := -Wall -Wextra -Werror -g
ASAN         := 1 # TODO

SRCDIR       := src
INCDIR       := include
OBJDIR       := target
RLLIBDIR     := /opt/homebrew/Cellar/readline/8.2.13# TODO

SRC          := main.c lexer.c lexer_case_string.c lexer_case_single.c \
				lexer_case_double.c lexer_helper_1.c lexer_helper_2.c \
				ast_node.c ast_parser.c ast_utils.c ast_handlers.c
OBJ          := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

INCFLAGS     := -I$(RLLIBDIR)/include -Iinclude
LIBFLAGS     := -L$(RLLIBDIR)/lib -lreadline

NAME         := minishell

ifneq ($(ASAN),0)
	CCFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(LIBFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CCFLAGS) $(INCFLAGS) -o $@ -c $<

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
