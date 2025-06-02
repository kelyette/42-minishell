CC           ?= gcc # TODO
RM           := rm -rf

CCFLAGS      := -Wall -Wextra -Werror -g
ASAN         ?= 0# TODO

SRCDIR       := src
INCDIR       := include
OBJDIR       ?= target
MODULES      := core envp lexer parser builtins executor
OBJDIRS      := $(addprefix $(OBJDIR)/,$(MODULES))
LIBFTDIR     := libft
RLLIBDIR     := /opt/homebrew/Cellar/readline/8.2.13# TODO

SRC          := $(addprefix core/,main.c signal.c)
SRC          += $(addprefix envp/,envp.c envp_helper_1.c envp_helper_2.c\
                    exit_code_handler.c)
SRC          += $(addprefix lexer/,lexer.c lexer_case_string.c \
                    lexer_case_single.c lexer_case_double.c \
                    lexer_helper_1.c dollar_handler.c dollar_handler_helper.c)
SRC          += $(addprefix parser/,parser.c node.c handlers.c utils.c)
SRC          += $(addprefix builtins/,builtins.c builtins_cd.c builtins_exit.c \
                    builtins_echo_pwd_env.c builtins_export.c builtins_unset.c \
                    builtins_cd_helper.c builtins_export_helper.c)
SRC          += $(addprefix executor/,executor.c utils.c path_utils.c tkn_utils.c \
                    pipe_utils.c case_cmd.c case_redir.c case_bin_pipe.c)
OBJ          := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
LIBFT        := $(LIBFTDIR)/libft.so

INCFLAGS     := -I$(RLLIBDIR)/include -I$(LIBFTDIR) -Iinclude
LDIRFLAGS    := -L$(RLLIBDIR)/lib -L$(LIBFTDIR)
LFLAGS       := -lreadline -lft

NAME         ?= minishell

ifneq ($(ASAN),0)
	CCFLAGS += -fsanitize=address
endif

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(LDIRFLAGS) -o $@ $^ $(LFLAGS)
	@echo "Built $@"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIRS)
	$(CC) $(CCFLAGS) $(LDIRFLAGS) $(INCFLAGS) -o $@ -c $<

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(OBJDIRS):
	@mkdir -p $@

clean:
	@$(RM) $(OBJDIR)
	@echo "Deleted object files"

fclean: clean
	@$(RM) $(NAME)
	@echo "Deleted $(NAME)"

re: fclean all

.PHONY: all clean fclean re
