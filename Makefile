CC           := cc
RM           := rm -rf

CCFLAGS      := -Wall -Wextra -Werror -g
ASAN         := 1 # TODO

SRCDIR       := src
INCDIR       := include
OBJDIR       := target
RLLIBDIR     ?= /opt/homebrew/Cellar/readline/8.2.13# TODO

SRC          := minishell.c init.c prompt_handler.c
OBJ          := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

LIBFLAGS     := -I$(RLLIBDIR)/include -L$(RLLIBDIR)/lib -lreadline# TODO

NAME         := minishell

ifneq ($(ASAN),0)
	CCFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(LIBFLAGS) -I$(INCDIR) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CCFLAGS) -I$(INCDIR) -o $@ -c $<

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
