CC           := cc
AR           := ar rcs

CCFLAGS      := -Wall -Wextra -Werror -g

STATICDIR    := target_static
SHAREDDIR    := target_shared
OBJDIR       := $(STATICDIR)

SRC  := ft_chrop.c ft_integer.c ft_io.c ft_ischr.c ft_mem_copy.c \
        ft_mem_set.c ft_mem_simple.c ft_str_copy.c ft_str_edit.c \
        ft_str_index.c ft_str_simple.c ft_str_comb.c ft_lst_iter.c \
        ft_lst_manage.c ft_lst_simple.c get_next_line.c format_char.c \
        format_int.c format_misc.c format_utils.c parser.c ft_printf.c

OBJSTATIC    := $(addprefix $(STATICDIR)/,$(SRC:.c=.o))
OBJSHARED    := $(addprefix $(SHAREDDIR)/,$(SRC:.c=.o))

NAME         := libft

ifeq ($(x86),1)
	CCWFLAGS += -arch x86_64
endif
ifeq ($(arm64),1)
	CCWFLAGS += -arch arm64
endif

all: $(NAME).a
so: $(NAME).so

$(NAME).a: $(OBJSTATIC)
	$(AR) $@ $^

$(NAME).so: OBJCCFLAGS = -fPIC
$(NAME).so: OBJDIR := $(SHAREDDIR)
$(NAME).so: $(OBJSHARED)
	$(CC) $(CCWFLAGS) -shared -o $(NAME).so $^

$(STATICDIR)/%.o $(SHAREDDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CCWFLAGS) $(OBJCCFLAGS) -c $< -o $@

clean:
	rm -rf $(STATICDIR) $(SHAREDDIR)

fclean: clean
	rm -f $(NAME).a $(NAME).so

re: fclean all

.PHONY: all a so clean fclean re
