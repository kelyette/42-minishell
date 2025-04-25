CC           := gcc # TODO
RM           := rm -rf

CCFLAGS      := -Wall -Wextra -Werror -g
ASAN         := 1 # TODO

SRCDIR       := src
MODULES      := core envp lexer parser executor
INCDIR       := include
OBJDIR       := target
OBJDIRS      := $(addprefix $(OBJDIR)/,$(MODULES))
RLLIBDIR     := /opt/homebrew/Cellar/readline/8.2.13# TODO

SRC          := $(addprefix core/,main.c signal.c libft.c)
SRC          += $(addprefix envp/,envp.c envp_helper_1.c envp_helper_2.c)
SRC          += $(addprefix lexer/,lexer.c lexer_case_string.c \
					lexer_case_single.c lexer_case_double.c \
					lexer_helper_1.c lexer_helper_2.c dollar_handler.c \
					dollar_handler_helper_1.c dollar_handler_helper_2.c)
SRC          += $(addprefix parser/,parser.c node.c handlers.c utils.c)
SRC          += $(addprefix executor/,executor.c utils.c case_cmd.c\
					case_redir.c case_bin_pipe.c)
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

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIRS)
	$(CC) $(CCFLAGS) $(INCFLAGS) -o $@ -c $<

$(OBJDIRS):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
